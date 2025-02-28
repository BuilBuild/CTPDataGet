/*
 * @Author: LeiJiulong
 * @Date: 2025-02-25 23:42:58
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-28 13:47:14
 * @Description:
 */

#include "Trader/OMS/CTPOMS.h"
#include "protos/MarketData.pb.h"

CTPOMS::CTPOMS(const OMSConfig &cfg)
    : context_(1), subscriber_(context_, zmq::socket_type::sub)
{
    subscriber_.connect(cfg.MarketSubAddress.c_str());
    subscriber_.set(zmq::sockopt::subscribe, "MarketData");
    if (subscriber_)
    {
        std::cout << "CTPOMS::connect success" << std::endl;
        marketDataThread_ = std::thread(&CTPOMS::marketDataReceive, this);
    }
    else
    {
        std::cout << "CTPOMS::connect failed" << std::endl;
    }
}

CTPOMS::~CTPOMS()
{
    if (marketDataThread_.joinable())
    {
        marketDataThread_.join();
    }
}

OrderID CTPOMS::createOrder(const OrderRequest &req)
{
    return 0;
}

bool cancelOrder(OrderID id)
{
    return false;
}

OrderStatus CTPOMS::getOrderStatus(OrderID id) const
{
    return OrderStatus::Rejected;
}

std::vector<Order> CTPOMS::getOpenOrders() const
{
    return {};
}

bool CTPOMS::connect(const std::string &config)
{
    return false;
}

void CTPOMS::disconnect() {}

bool CTPOMS::isConnected() const { return false; }

void CTPOMS::marketDataReceive() 
{
    while (true)
    {
        
        marketdata::MarketData md;
        zmq::message_t topic, message;
        if (auto res = subscriber_.recv(topic, zmq::recv_flags::none))
        {
            // 接取行情数据
            if(subscriber_.recv(message, zmq::recv_flags::none))
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

void CTPOMS::registerCallback(std::function<void(const OrderEvent &)> cb) {}

void CTPOMS::start() {}

void CTPOMS::stop() {}
