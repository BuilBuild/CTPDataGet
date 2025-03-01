/*
 * @Author: LeiJiulong
 * @Date: 2025-02-28 08:08:18
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-01 09:32:50
 * @Description: 
 */
#pragma once

#include "IStrategy.h"
#include "Trader/TraderBaseType.hpp"

#include <zmq.hpp>
#include <memory>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

// CTP策略配置
typedef struct ICTPStrategyConfig 
{
    // 订阅合约
    std::vector<std::string> instruments_;
    // 订阅地址
    std::string subAddr_;
    // 订单发送地址
    std::string orderAddr_;

} ICTPStrategyConfig;

// CTP策略基类
class ICTPStrategy : public IStrategy
{
public:
    ICTPStrategy() = delete;
    explicit ICTPStrategy(const ICTPStrategyConfig& config);
    virtual ~ICTPStrategy();
    // 行情数据接收
    virtual void OnMarketData() override;
    // 添加叮当
    virtual void addOrder(const OrderRequest &orderRequest);

    // 发送交易请求
    virtual void SendOrder(const OrderRequest &orderRequest) override;
    // 接收交易回报
    virtual void OnTradeReport() override;
    
    // 查询持仓信息
    virtual void OnPositionReport() override;
    // 其他信息查询
    virtual void OnQuery() override;
    // 其他信息回报
    virtual void OnQueryReport() override;

    // 生命周期管理
    virtual void OnInit() override;
    virtual void Start() override;
    virtual void Stop() override;
    
    // 订阅行情数据
    virtual void subscribeMarketData(const std::string &instrument);
    // 取消订阅行情数据
    virtual void unsubscribeMarketData(const std::string &instrument);

    // 策略参数配置
    virtual void SetConfig(const StrategyConfig &config) override;

    // 订单处理线程
    virtual void orderThreadFunc();

protected:
    // 策略配置
    StrategyConfig strategyConfig_;
    // zmq上下文
    zmq::context_t context_;
    // 行情数据接收
    zmq::socket_t marketDataSubscribe_;
    // 交易回报接收
    zmq::socket_t tradeReportSubscribe_;
    
    // 行情处理线程
    std::thread marketDataThread_;
    // 订单生成队列
    std::queue<OrderRequest> orderQueue_;
    // 订单队列锁
    std::mutex orderQueueMutex_;
    // 订单队列条件变量
    std::condition_variable orderQueueCondition_;
    // 订单发送与消息回报线程
    std::thread orderThread_;

};


