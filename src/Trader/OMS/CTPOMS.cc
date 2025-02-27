/*
 * @Author: LeiJiulong
 * @Date: 2025-02-25 23:42:58
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-27 07:56:20
 * @Description:
 */

#include "Trader/OMS/CTPOMS.h"

CTPOMS::CTPOMS(const OMSConfig &cfg)
    : context_(1), subscriber_(context_, zmq::socket_type::sub)
{
    bool flag = connect(cfg.connetAddr_);
    if (flag)
    {
        marketDataThread_ = std::thread(&CTPOMS::marketDataReceive, this);
    }
    else
    {
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

void marketDataReceive() {}

void CTPOMS::registerCallback(std::function<void(const OrderEvent &)> cb) {}

void CTPOMS::start() {}

void CTPOMS::stop() {}