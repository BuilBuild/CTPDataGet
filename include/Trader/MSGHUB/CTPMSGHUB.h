/*
 * @Author: LeiJiulong
 * @Date: 2025-02-27 13:20:40
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-27 15:47:14
 * @Description: 
 */
#pragma once

#include "IMSGHUB.h"
#include "Trader/LOB/CTPLOB.h"

#include <zmq.hpp>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
// #include <atomic>
#include <string>
#include <queue>


class CTPMSGHUB : public IMSGHUB
{

public:
    CTPMSGHUB();
    virtual ~CTPMSGHUB();
    // 初始化
    virtual void Init(const MSGHUBConfig& config) override;
    // 启动
    virtual void Start() override;
    // 停止
    virtual void Stop() override;
    // 行情数据写入
    virtual void WriteMarketData(const OrderBook& orderBook) override;
    
private:
    virtual void SubMarketData() override;
    virtual void PubMarketData() override;
    
    void marketDataPub(const OrderBook& orderBook);

private:
    // 用于接收行情数据的socket
    std::unique_ptr<zmq::context_t> contextMarketReceive_;
    std::unique_ptr<zmq::socket_t> socketMarketReceive_;
    // 用于发布行情数据的socket
    std::unique_ptr<zmq::context_t> contextMarketPublish_;
    std::unique_ptr<zmq::socket_t> socketMarketPublish_;
    
    // 内部订单簿
    std::unique_ptr<CTPILOB> lob_;
    // 行情数据发布线程
    std::thread marketDataPublishThread_;
    // 行情数据队列缓冲区
    std::queue<OrderBook> marketDataQueue_;
    // 行情数据队列缓冲区锁
    std::mutex marketDataQueueMutex_;
    // 行情数据队列缓冲区条件变量
    std::condition_variable marketDataQueueCondition_;
    
};
