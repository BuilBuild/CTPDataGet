/*
 * @Author: LeiJiulong
 * @Date: 2025-02-25 08:48:06
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-25 08:56:43
 * @Description: 
 */

#include "Trader/LOB/CTPLOB.h"


// 更新订单簿
void CTPLimitOrderBook::updateOrderBook(const OrderBook& orderBook)
{

}
// 获取订单簿
OrderBook CTPLimitOrderBook::getOrderBook()
{
    return OrderBook{};
}
// 获取最佳买价
double CTPLimitOrderBook::getBestBidPrice()
{
    return 0.0;
}
// 获取最佳卖价
double CTPLimitOrderBook::getBestAskPrice()
{
    return 0.0;
}
// 获取最佳买量
int CTPLimitOrderBook::getBestBidVolume()
{
    return 0;
}
// 获取最佳卖量
int CTPLimitOrderBook::getBestAskVolume()
{
    return 0;
}
// 获取最佳买价和最佳卖价之间的价差
double CTPLimitOrderBook::getSpread()
{
    return 0.0;
}
// 获取最佳买价和最佳卖价之间的价差百分比
double CTPLimitOrderBook::getSpreadPercentage()
{
    return 0.0;
}
// 获取订单簿深度
int CTPLimitOrderBook::getDepth()
{
    return 0;
}
// 获取订单簿时间
Timestamp CTPLimitOrderBook::getUpdateTime()
{
    return Timestamp{};
}

// 创建订单簿
std::unique_ptr<LimitOrderBook> CTPILOB::createLimitOrderBook(const std::string& symbol)
{
    return std::make_unique<CTPLimitOrderBook>();
}
// 获取订单簿
LimitOrderBook* CTPILOB::getLimitOrderBook(const std::string& symbol)
{
    return nullptr;
}
// 移除订单簿
void CTPILOB::removeLimitOrderBook(const std::string& symbol)
{

}
// 添加订单簿
void CTPILOB::addLimitOrderBook(const std::string& symbol, std::unique_ptr<LimitOrderBook> lob)
{

}
