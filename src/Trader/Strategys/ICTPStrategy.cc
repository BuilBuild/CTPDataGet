/*
 * @Author: LeiJiulong
 * @Date: 2025-02-28 08:10:34
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-04 20:07:56
 * @Description: 
 */

#include "Trader/Strategys/ICTPStrategy.h"
#include "protos/MarketData.pb.h"
#include "protos/message.pb.h"
#include "SelfUtils.hpp"

#include <sstream>

#include <iostream>

ICTPStrategy::ICTPStrategy(const ICTPStrategyConfig& config)
    :context_(1), marketDataSubscribe_(context_, zmq::socket_type::sub), tradeReportSubscribe_( context_, zmq::socket_type::req)
{
    // 注册日志
    
    logger_ = LogSystem::RegisterLogger("ICTPStrategy");

    marketDataSubscribe_.connect(config.subAddr_.c_str());
    for(auto ins : config.instruments_)
    {
        subscribeMarketData(ins);
    }
    if(marketDataSubscribe_)
    {
        LOG_INFO("ICTPStrategy::ICTPStrategy success");
        tradeReportSubscribe_.connect(config.orderAddr_.c_str());
    }
    else
    {
        exit(-1);
    }
    // 订阅行情线程
    if(tradeReportSubscribe_)
    {
        std::cout << "ICTPStrategy::ICTPStrategy success" << std::endl;
        marketDataThread_ = std::thread(&ICTPStrategy::OnMarketData, this);
    }
    else
    {
        exit(-1);
    }
    // 发送订单旱情
    tradeReportSubscribe_.connect(config.orderAddr_.c_str());
    if(tradeReportSubscribe_)
    {
        std::cout << "ICTPStrategy::ICTPStrategy Order Send connect success" << std::endl;
        // 启动订单处理线程
        orderThread_ = std::thread(&ICTPStrategy::orderThreadFunc, this);
    }

}

ICTPStrategy::~ICTPStrategy()
{
    if(marketDataThread_.joinable())
    {
        marketDataThread_.join();
    }
    if(orderThread_.joinable())
    {
        orderThread_.join();
    }
}

// 行情数据接收
 void ICTPStrategy::OnMarketData() 
 {
    while(true)
    {
        marketdata::MarketData md;
        zmq::message_t topic, message;
        if (auto res = marketDataSubscribe_.recv(topic, zmq::recv_flags::none))
        {
            // 接取行情数据
            if(marketDataSubscribe_.recv(message, zmq::recv_flags::none))
            {
                // std::cout << "Received " << *res << " bytes: "<< message.to_string_view() << std::endl;
                md.ParseFromArray(message.data(), message.size());
                std::cout << "Received MarketData: " << md.DebugString() << std::endl;
            }
            else
            {
                // 获取错误码
                int error_code = zmq_errno();
                std::cerr << "Receive failed (error: " << error_code << ")"
                          << " - " << zmq_strerror(error_code) << std::endl;
            }
        }
        else
        {
            // 获取错误码
            int error_code = zmq_errno();
            std::cerr << "Receive failed (error: " << error_code << ")"
                      << " - " << zmq_strerror(error_code) << std::endl;
        }
    }

 }

 void ICTPStrategy::addOrder(const OrderRequest &orderRequest)
 {
    // 获取锁
    std::lock_guard<std::mutex> lock(orderQueueMutex_);
    orderQueue_.emplace(orderRequest);
    std::string msg = "Add Order: ";
    msg = msg + orderRequest.symbol + " " + std::to_string(orderRequest.orderId);
    LOG_INFO(msg);
    orderQueueCondition_.notify_one();

 }

 // 发送交易请求
 void ICTPStrategy::SendOrder(const OrderRequest &orderRequest)
 {
    LOG_INFO("ICTPStrategy::SendOrder");
    std::string msg = "SendOrder: ";
    msg = msg + orderRequest.symbol + " " + std::to_string(orderRequest.orderId);
    LOG_INFO(msg);
    // 序列化订单信息
    message::OrderRequest orderRequestMessage;
    orderRequestMessage.set_instrumentid(orderRequest.symbol);
    orderRequestMessage.set_order_id(orderRequest.orderId);
    orderRequestMessage.set_time_stamp(SelfUtil::get_timestamp());

    zmq::message_t orderRequestMessageBuffer(orderRequestMessage.SerializeAsString());
    tradeReportSubscribe_.send(orderRequestMessageBuffer, zmq::send_flags::none);
    // 接收回报
    zmq::message_t tradeReportMessage;
    if(tradeReportSubscribe_.recv(tradeReportMessage, zmq::recv_flags::none))
    {
        // 反序列化回报信息
        message::OrderResponse orderRes;
        orderRes.ParseFromArray(tradeReportMessage.data(), tradeReportMessage.size());
        std::ostringstream oss;
        oss << "OrderResponse: " << orderRes.instrumentid() << " " << orderRes.order_id() << " " << orderRes.status();
        LOG_INFO(oss.str());
    }
    else
    {
        // 获取错误码
        int error_code = zmq_errno();
        std::cerr << "Receive failed (error: " << error_code << ")"
                  << " - " << zmq_strerror(error_code) << std::endl;
    }
 }
// 接收交易回报
 void ICTPStrategy::OnTradeReport() {}

// 查询持仓信息
 void ICTPStrategy::OnPositionReport() {}
// 其他信息查询
 void ICTPStrategy::OnQuery() {}
// 其他信息回报
 void ICTPStrategy::OnQueryReport() {}

// 生命周期管理
 void ICTPStrategy::OnInit() {}
 void ICTPStrategy::Start() {}
 void ICTPStrategy::Stop() {}

// 订阅行情数据
void ICTPStrategy::subscribeMarketData(const std::string &instrument)
{
    std::string topic;
    topic = topic + "MarketData." + instrument;
    marketDataSubscribe_.set(zmq::sockopt::subscribe, topic);
}

// 取消订阅市场数据
void ICTPStrategy::unsubscribeMarketData(const std::string &instrument)
{

}

// 策略参数配置
 void ICTPStrategy::SetConfig(const StrategyConfig &config) {}

 void ICTPStrategy::orderThreadFunc()
 {
    while(true)
    {
        std::unique_lock<std::mutex> lock(orderQueueMutex_);
        // 发送订单
        orderQueueCondition_.wait(lock, [this](){return !orderQueue_.empty();});
        auto order = std::move(orderQueue_.front());
        SendOrder(order);
        orderQueue_.pop();
    }
 }
