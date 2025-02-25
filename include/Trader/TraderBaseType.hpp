/*
 * @Author: LeiJiulong
 * @Date: 2025-02-22 21:52:42
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-26 01:35:48
 * @Description:
 */
#pragma once

#include <string>
#include <variant>
#include <vector>
#include <unordered_map>
#include <optional>
#include <chrono>
#include <mutex>
#include <atomic>
#include <tbb/concurrent_queue.h>
#include <tbb/concurrent_map.h>

// 时间戳
using Timestamp = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;

using OrderID  = int64_t;

// 事件优先级
enum class EventPriority
{
    High,  // 高
    Normal, // 中
    Low    // 低
};

// 订单状态
enum class OrderStatus
{
    New,             // 新订单
    PartiallyFilled, // 部分成交
    Filled,          // 全部成交
    Canceled,        // 已撤销
    Rejected         // 已拒绝
};

// 订单类型
enum class OrderType
{
    Market,       // 市价单
    Limit,        // 限价单
    IOC,          // 即时成交或取消
    Stop,         // 止损单
    StopLimit,    // 限价止损单
    TrailingStop, // 跟踪止损单
    Iceberg,      // 冰山单
    TWAP,         // TWAP
    VWAP          // VWAP
};

// 买卖方向
enum class Side
{
    Buy, // 买
    Sell // 卖
};

// 分片状态
enum class SliceState
{
    Pending, // 待发送
    Sent,    // 已发送
    Filled,  // 已成交
    Canceled // 已撤销
};

// 订单方向
enum class OrderSide
{
    Buy, // 买
    Sell // 卖
};
// 风控检查结果
enum class RiskCheckResult
{
    Pass,    // 通过
    Warning, // 警告
    Block    // 阻塞
};

enum class RoutingLogic
{
    PricePriority,
    LiquidityPriority
};

// 时间有效性模式
enum class TimeRangeType
{
    ABSOLUTE_TIME,  // 绝对时间窗口
    RELATIVE_DELAY, // 相对母单的时间偏移
    MARKET_SESSION  // 交易所交易时段
};

// 交易所状态
typedef struct TimeRange
{
    // 核心字段
    TimeRangeType type;
    Timestamp startTime; // UTC时间戳
    Timestamp endTime;   // UTC时间戳

    // 动态调整参数（仅对RELATIVE_DELAY有效）
    int64_t min_delay_ms = 0;   // 最小延迟
    int64_t max_delay_ms = 500; // 最大延迟

    // 交易所时段映射（仅对MARKET_SESSION有效）
    std::string exchange_code;    // 交易所代码（如"XNYS"）
    bool extendPreMarket = false; // 是否包含盘前
} TimeRange;

// 订单请求
typedef struct OrderRequest
{
    OrderID orderId; // 订单ID
    std::string symbol;  // 交易标的
    OrderSide side;      // 买卖方向
    double price;        // 价格
    int quantity;        // 数量
    OrderType type;      // 订单类型
    TimeRange validTime; // 有效时间窗口
    std::string account;  // 账户
    std::string exchange; // 交易所
    Timestamp timestamp; // 时间戳
} OrderRequest;

// 执行报告
typedef struct ExecutionReport
{
    std::string execId;  // 执行ID
    OrderID orderId; // 订单ID
    double filledPrice;  // 成交价
    int filledQty;       // 成交数量
    OrderStatus status;  // 订单状态
    Timestamp timestamp; // 时间戳
    // ... 其他字段
} ExecutionReport;

// 风控参数
typedef struct RiskParams
{
    double maxPositionLimit;    // 最大持仓限制
    double maxOrderSize;        // 最大单笔下单量
    double volatilityThreshold; // 波动率阈值
} RiskParams;

typedef struct OrderSlice
{
    uint64_t sliceId;    // 唯一分片标识
    OrderType type;      // LIMIT/MARKET/IOC等
    Side direction;      // BUY/SELL
    double price;        // 定价（可动态计算）
    int64_t quantity;    // 分片数量
    TimeRange validTime; // 分片有效时间窗口
    SliceState state;    // PENDING/SENT/FILLED/CANCELED
    // 其他字段：滑点容忍度、优先级等
} OrderSlice;

// 市场数据事件（支持多数据类型）
typedef struct MarketDataEvent
{
    std::string symbol;  // 交易标的
    Timestamp timestamp; // 时间戳
    // std::variant<TickData, OrderBookSnapshot, Trade> data;
} MarketDataEvent;

// 执行策略配置
typedef struct ExecutionStrategyConfig
{
    std::string algorithmName; // 算法名称（如 VWAP）
    double urgency;            // 执行紧急度 (0~1)
    int maxParticipationRate;  // 最大市场参与率 (%)
    bool allowDarkPool;        // 是否允许暗池交易
    // ... 其他风控参数
} ExecutionStrategyConfig;

// 执行算法参数
typedef struct ExecutionParameters
{
    OrderRequest baseOrder;    // 原始订单
    TimeRange executionWindow; // 执行时间窗口
    int sliceCount;            // 分片数量（TWAP 分片）
    double maxDeviation;       // 允许的价格偏离
} ExecutionParameters;

// 路由决策结果
typedef struct RouteDecision
{
    std::string venue;        // 目标交易场所
    double expectedFillPrice; // 预期成交价
    int allocatedQuantity;    // 分配数量
    RoutingLogic logic;       // 路由逻辑（价格优先/流动性优先）
} RouteDecision;

// 交易所状态
typedef struct ExchangeStatus
{
    std::string exchangeCode; // 交易所代码
    bool isOnline;            // 是否在线
    double latency;           // 延迟（毫秒）
} ExchangeStatus;

// 交易所状态更新
typedef struct ExchangeStatusUpdate
{
    std::string exchangeCode; // 交易所代码
    bool isOnline;            // 是否在线
    double latency;           // 延迟（毫秒）
    Timestamp timestamp;      // 更新时间
} ExchangeStatusUpdate;

// 交易所状态订阅请求
typedef struct ExchangeStatusSubscription
{
    std::vector<std::string> exchanges; // 交易所代码列表
} ExchangeStatusSubscription;

// 订单拒绝原因
typedef struct OrderRejection
{
    OrderID orderId; // 订单ID
    std::string reason;  // 拒绝原因
    Timestamp timestamp; // 拒绝时间
} OrderRejection;

typedef struct OrderEvent
{
    EventPriority priority;
    OrderID orderId;
    OrderStatus status;
    Timestamp timestamp;
} OrderEvent;

// 雪花算法OrderID生成
namespace snowid
{
    class Snowflake
    {
    public:
        Snowflake(uint16_t machine_id, uint16_t datacenter_id)
            : machine_id_(machine_id & 0x1F),
              datacenter_id_(datacenter_id & 0x1F),
              sequence_(0),
              last_timestamp_(0) {}

        int64_t Generate()
        {
            std::lock_guard<std::mutex> lock(mutex_);
            auto timestamp = CurrentTimestamp();

            if (timestamp < last_timestamp_)
            {
                throw std::runtime_error("Clock moved backwards");
            }

            if (timestamp == last_timestamp_)
            {
                sequence_ = (sequence_ + 1) & 0xFFF;
                if (sequence_ == 0)
                {
                    timestamp = WaitNextMillis(timestamp);
                }
            }
            else
            {
                sequence_ = 0;
            }

            last_timestamp_ = timestamp;
            return ((timestamp - EPOCH) << 22) |
                   (datacenter_id_ << 17) |
                   (machine_id_ << 12) |
                   sequence_;
        }

    private:
        // 可以自行配置 
        const int64_t EPOCH = 1577836800000; // 2020-01-01
        uint16_t machine_id_;
        uint16_t datacenter_id_;
        uint16_t sequence_;
        int64_t last_timestamp_;
        std::mutex mutex_;

        int64_t CurrentTimestamp()
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(
                       std::chrono::system_clock::now().time_since_epoch())
                .count();
        }

        int64_t WaitNextMillis(int64_t timestamp)
        {
            while (timestamp <= last_timestamp_)
            {
                timestamp = CurrentTimestamp();
            }
            return timestamp;
        }
    };

}

typedef struct Order {
    OrderID orderId;      // 原子递增ID（确保无锁唯一性）
    std::string symbol;          // 标的代码（使用flyweight模式优化内存）
    Side side;              // 买卖方向（枚举：BUY/SELL）
    OrderType type;         // 订单类型（LIMIT/MARKET/IOC等）
    double price;           // 价格（定点数优化，避免浮点误差）
    int64_t quantity;       // 原始数量（支持大整数）
    int64_t filledQty;     // 已成交数量（原子操作）
    OrderStatus status;     // 状态机（NEW/PARTIALLY_FILLED/FILLED/CANCELED等）
    time_t timestamp;       // 高精度时间戳（纳秒级）
    // ... 风控标记/策略ID等扩展字段
} Order;

struct PriceLevel {
    int64_t price;               // 价格（使用定点数避免浮点误差）
    std::atomic<int64_t> total_qty; // 该价位总数量（原子操作）
    tbb::concurrent_queue<Order*> orders;
    // ... 扩展字段
};


class RMSOrderBook 
{
public:
    // ... 订单簿数据结构定义
    // ... 订单簿操作接口定义
    void insertOrder(Order* order)
    {

    }
    void cancelOrder(Order* order){};
    void updateOrder(Order* order){};
    void matchOrder(Order* order){};
    // ... 其他操作接口
public:
    using PriceQueue = tbb::concurrent_bounded_queue<Order>;      // 同一价格的订单队列
    using BidMap = tbb::concurrent_map<double, PriceQueue, std::greater<double>>;  // 买单价降序
    using AskMap = tbb::concurrent_map<double, PriceQueue>;  // 卖单价升序

    BidMap bids;   // 买单
    AskMap asks;   // 卖单



};