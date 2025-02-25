/*
 * @Author: LeiJiulong
 * @Date: 2025-02-25 08:19:11
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-25 09:33:34
 * @Description: 
 */
#pragma once

#include "MarketData/BaseType.hpp"
#include "Trader/TraderBaseType.hpp"
#include "NonCopyAble.hpp"

#include <string>
#include <memory>
#include <tbb/concurrent_map.h>
#include <tbb/concurrent_queue.h>
#include <mutex>
#include <thread>

class LimitOrderBook
{
public:
    LimitOrderBook() = default;
    virtual ~LimitOrderBook() = default;

    // 更新订单簿
    virtual void updateOrderBook(const OrderBook& orderBook) = 0;
    // 获取订单簿
    virtual OrderBook getOrderBook() = 0;
    // 获取最佳买价
    virtual double getBestBidPrice() = 0;
    // 获取最佳卖价
    virtual double getBestAskPrice() = 0;
    // 获取最佳买量
    virtual int getBestBidVolume() = 0;
    // 获取最佳卖量
    virtual int getBestAskVolume() = 0;
    // 获取最佳买价和最佳卖价之间的价差
    virtual double getSpread() = 0;
    // 获取最佳买价和最佳卖价之间的价差百分比
    virtual double getSpreadPercentage() = 0;
    // 获取订单簿深度
    virtual int getDepth() = 0;
    // 获取订单簿时间
    virtual const Timestamp& getUpdateTime() = 0;
protected:
    std::mutex mutex_;
    OrderBook orderBook_{};
    Timestamp updateTime_{};
};


class ILOB : public NonCopyAble
{
private:
    /* data */
public:
    ILOB() = default;
    ~ILOB() = default;
    // 创建订单簿
    virtual std::unique_ptr<LimitOrderBook> createLimitOrderBook(const std::string& symbol) = 0;
    // 获取订单簿
    virtual LimitOrderBook* getLimitOrderBook(const std::string& symbol) = 0;
    // 移除订单簿
    virtual void removeLimitOrderBook(const std::string& symbol) = 0;
    // 添加订单簿
    virtual void addLimitOrderBook(const std::string& symbol, std::unique_ptr<LimitOrderBook> lob) = 0;
    virtual void addOrderBook(const OrderBook& orderBook) = 0;
protected:
    // 订单簿映射
    tbb::concurrent_map<std::string, std::unique_ptr<LimitOrderBook>> lobMap_;
    // 订单簿队列
    tbb::concurrent_bounded_queue<OrderBook> orderBookQueue_;
    // 订单簿队列互斥量
    std::mutex orderBookQueueMutex_;
    // 订单簿队列线程
    std::thread orderBookThread_;

};



