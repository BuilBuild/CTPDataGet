/*
 * @Author: LeiJiulong
 * @Date: 2025-02-25 08:48:06
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-25 10:15:17
 * @Description: 
 */

#include "Trader/LOB/CTPLOB.h"
#include <spdlog/spdlog.h>


// 更新订单簿
void CTPLimitOrderBook::updateOrderBook(const OrderBook& orderBook)
{
    std::lock_guard<std::mutex> lck(mutex_);
    memcpy(&orderBook_, &orderBook, sizeof(OrderBook));
    updateTime_ = std::chrono::system_clock::now();
}
// 获取订单簿
OrderBook CTPLimitOrderBook::getOrderBook()
{
    std::lock_guard<std::mutex> lck(mutex_);
    return orderBook_;
}
// 获取最佳买价
double CTPLimitOrderBook::getBestBidPrice()
{   
    std::lock_guard<std::mutex> lck(mutex_);
    return orderBook_.BidPrice1;
}
// 获取最佳卖价
double CTPLimitOrderBook::getBestAskPrice()
{
    std::lock_guard<std::mutex> lck(mutex_);
    return orderBook_.AskPrice1;
}
// 获取最佳买量
int CTPLimitOrderBook::getBestBidVolume()
{
    std::lock_guard<std::mutex> lck(mutex_);
    return orderBook_.BidVolume1;
}
// 获取最佳卖量
int CTPLimitOrderBook::getBestAskVolume()
{
    std::lock_guard<std::mutex> lck(mutex_);
    return orderBook_.AskVolume1;
}
// 获取最佳买价和最佳卖价之间的价差
double CTPLimitOrderBook::getSpread()
{
    std::lock_guard<std::mutex> lck(mutex_);
    return orderBook_.AskPrice1 - orderBook_.BidPrice1;
}
// 获取最佳买价和最佳卖价之间的价差百分比
double CTPLimitOrderBook::getSpreadPercentage()
{
    std::lock_guard<std::mutex> lck(mutex_);
    return (orderBook_.AskPrice1 - orderBook_.BidPrice1) / orderBook_.BidPrice1;
}
// 获取订单簿深度
int CTPLimitOrderBook::getDepth()
{
    return 1;
}
// 获取订单簿时间
const Timestamp& CTPLimitOrderBook::getUpdateTime()
{
    return updateTime_;
}

// 创建订单簿
std::unique_ptr<LimitOrderBook> CTPILOB::createLimitOrderBook(const std::string& symbol)
{
    return std::make_unique<CTPLimitOrderBook>();
}
// 获取订单簿
LimitOrderBook* CTPILOB::getLimitOrderBook(const std::string& symbol)
{
    auto flag = lobMap_.find(symbol);
    if (flag != lobMap_.end())
    {
        return flag->second.get();
    }
    else
    {
        auto lob = createLimitOrderBook(symbol);
        lobMap_.insert(std::make_pair(symbol, std::move(lob)));
        return lobMap_[symbol].get();
    }
}

CTPLimitOrderBook::CTPLimitOrderBook()
{
    std::unique_lock<std::mutex> lck(mutex_);
    orderBook_ = OrderBook{};
    updateTime_ = std::chrono::system_clock::now();
}

CTPILOB::CTPILOB()
{
    lobMap_.clear();
    orderBookThread_ = std::thread([this](){
        while (true)
        {
            OrderBook ob{};
            orderBookQueue_.pop(ob);
            auto lob = getLimitOrderBook(ob.InstrumentID);
            if (lob)
            {
                lob->updateOrderBook(ob);
            }
        }
    });
}


// 移除订单簿
void CTPILOB::removeLimitOrderBook(const std::string& symbol)
{
    auto flag = lobMap_.find(symbol);
    if (flag != lobMap_.end())
    {
        lobMap_.unsafe_erase(symbol);
    }
}
// 添加订单簿
void CTPILOB::addLimitOrderBook(const std::string& symbol, std::unique_ptr<LimitOrderBook> lob)
{
    auto flag = lobMap_.find(symbol);
    if (flag == lobMap_.end())
    {
        lobMap_.insert(std::make_pair(symbol, std::move(lob)));
    }
    else
    {
        lobMap_[symbol] = std::move(lob);
    }
}

void CTPILOB::addOrderBook(const OrderBook& orderBook)
{
    orderBookQueue_.emplace(orderBook);
}
