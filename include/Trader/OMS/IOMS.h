/*
 * @Author: LeiJiulong
 * @Date: 2025-02-25 13:04:59
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-27 08:09:56
 * @Description:
 */
#pragma once

#include "Trader/TraderBaseType.hpp"
#include "NonCopyAble.hpp"
#include "Trader/ORMSConfig.hpp"

#include <functional>
#include <tbb/concurrent_queue.h>
#include <tbb/concurrent_map.h>
#include <tbb/concurrent_unordered_map.h>
#include <tbb/concurrent_priority_queue.h>
#include <zmq.hpp>

// 订单优先级比较器
class OrderEventComparator {
public:
    bool operator()(OrderEvent &a, OrderEvent &b) {
        return a.priority < b.priority;
    }
};

// 订单事件队列
using OrderEventQueue = tbb::concurrent_priority_queue<OrderEvent,OrderEventComparator>;

// OMS接口
class IOMS : public NonCopyAble
{
public:
    //---------- 订单操作接口 ----------
    virtual OrderID createOrder(const OrderRequest &req) = 0;
    // virtual bool modifyOrder(OrderID id, const OrderModify &mod) = 0;
    virtual bool cancelOrder(OrderID id) = 0;

    //---------- 状态查询接口 ----------
    virtual OrderStatus getOrderStatus(OrderID id) const = 0;
    virtual std::vector<Order> getOpenOrders() const = 0;

    //---------- 连接管理 ----------
    virtual bool connect(const std::string &config) = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;

    // ----------- 行情接收 ----------
    virtual void marketDataReceive() = 0;

    //---------- 事件订阅 ----------
    virtual void registerCallback(std::function<void(const OrderEvent &)> cb) = 0;

    //---------- 系统控制 ----------
    virtual void start() = 0; // 启动OMS
    virtual void stop() = 0;  // 停止OMS


protected:
    //---------- 内部工具方法 ----------
    // 订单ID生成逻辑
    virtual void generateOrderID(OrderRequest &req){}
    // 订单校验
    virtual bool validateOrder(const OrderRequest &req){ return false;}
    // 订单事件队列
    OrderEventQueue orderEventQueue_;
    // 订单列表
    tbb::concurrent_map<std::string, OMSOrderBook> orderBookMap_;
    // 活跃订单列表
    tbb::concurrent_unordered_map<int, Order> activeOrders_;
    // 已成交订单列表
    tbb::concurrent_unordered_map<int, Order> filledOrders_;
    // 更新订单队列
    tbb::concurrent_queue<Order> orderUpdatesQueue_;

};
