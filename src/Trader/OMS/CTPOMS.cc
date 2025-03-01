/*
 * @Author: LeiJiulong
 * @Date: 2025-02-25 23:42:58
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-01 14:14:44
 * @Description:
 */

#include "Trader/OMS/CTPOMS.h"
#include "protos/MarketData.pb.h"
#include "protos/message.pb.h"
#include "SelfUtils.hpp"

CTPOMS::CTPOMS(const OMSConfig &cfg)
    : context_(1), subscriber_(context_, zmq::socket_type::sub),replySocket_(context_, zmq::socket_type::rep)
{
    replySocket_.bind(cfg.OrderRequestAddress.c_str());
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
    if(replySocket_)
    {
        requestReplyThread_ = std::thread(&CTPOMS::requestReply, this);
    }
}

CTPOMS::~CTPOMS()
{
    if (marketDataThread_.joinable())
    {
        marketDataThread_.join();
    }
    if (requestReplyThread_.joinable())
    {
        requestReplyThread_.join();
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

void CTPOMS::registerCallback(std::function<void(const OrderEvent &)> cb) {}

void CTPOMS::start() {}

void CTPOMS::stop() {}

void CTPOMS::requestReply()
{
    while (true)
    {
        zmq::message_t request;
        if (auto res = replySocket_.recv(request, zmq::recv_flags::none))
        {
            // 序列化消息
            message::OrderRequest req;
            req.ParseFromArray(request.data(), request.size());
            std::cout << "Received OrderRequest: " << req.DebugString() << std::endl;
            // 处理请求
            message::OrderResponse resp;
            processOrderResponse(req, resp);
            // 序列化响应
            std::string respStr = resp.SerializeAsString();
            zmq::message_t reply(respStr.c_str(), respStr.size());
            // 发送响应
            replySocket_.send(reply, zmq::send_flags::none);
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

void CTPOMS::processOrderResponse(const message::OrderRequest &req, message::OrderResponse &resp)
{
    using namespace SelfUtil;
    // 风控
    // ........
    // 生成响应
    resp.set_order_id(req.order_id());
    resp.set_status(true);
    resp.set_code(1);
    resp.set_instrumentid(req.instrumentid());
    resp.set_time_stamp(get_timestamp());
    
}
