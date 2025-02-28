/*
 * @Author: LeiJiulong
 * @Date: 2025-02-28 08:10:34
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-28 14:44:43
 * @Description: 
 */

#include "Trader/Strategys/ICTPStrategy.h"
#include "protos/MarketData.pb.h"

#include <iostream>

ICTPStrategy::ICTPStrategy(const ICTPStrategyConfig& config)
    :context_(1), marketDataSubscribe_(context_, zmq::socket_type::sub)
{
    marketDataSubscribe_.connect(config.subAddr_.c_str());
    for(auto ins : config.instruments_)
    {
        subscribeMarketData(ins);
    }
    if(marketDataSubscribe_)
    {
        std::cout << "ICTPStrategy::ICTPStrategy success" << std::endl;
    }

    marketDataThread_ = std::thread(&ICTPStrategy::OnMarketData, this);
}

ICTPStrategy::~ICTPStrategy()
{
    if(marketDataThread_.joinable())
    {
        marketDataThread_.join();
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
                std::cout << "Received " << *res << " bytes: "<< message.to_string_view() << std::endl;
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
// 发送交易请求
 void ICTPStrategy::SendOrder() {}
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
