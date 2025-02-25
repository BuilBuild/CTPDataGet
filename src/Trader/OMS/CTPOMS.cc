/*
 * @Author: LeiJiulong
 * @Date: 2025-02-25 23:42:58
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-26 00:25:39
 * @Description:
 */

#include "Trader/OMS/CTPOMS.h"

CTPOMS::CTPOMS()
{
}

CTPOMS::~CTPOMS()
{
}

OrderID CTPOMS::createOrder(const OrderRequest &req)
{
}

bool cancelOrder(OrderID id) {}

//---------- 状态查询接口 ----------
OrderStatus CTPOMS::getOrderStatus(OrderID id) const {}
std::vector<Order> CTPOMS::getOpenOrders() const {}

//---------- 连接管理 ----------
bool CTPOMS::connect(const std::string &config) {}
void CTPOMS::disconnect() {}
bool CTPOMS::isConnected() const {}

//---------- 事件订阅 ----------
void CTPOMS::registerCallback(std::function<void(const OrderEvent &)> cb) {}

//---------- 系统控制 ----------
void CTPOMS::start() {} // 启动OMS
void CTPOMS::stop() {}  // 停止OMS
