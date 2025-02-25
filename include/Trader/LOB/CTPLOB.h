/*
 * @Author: LeiJiulong
 * @Date: 2025-02-25 08:30:32
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-25 08:52:52
 * @Description: 
 */
#pragma once

#include "ILOB.h"


class CTPLimitOrderBook : public LimitOrderBook
{
public:
    CTPLimitOrderBook() = default;
    virtual ~CTPLimitOrderBook() = default;

    // 更新订单簿
    virtual void updateOrderBook(const OrderBook& orderBook) override;
    // 获取订单簿
    virtual OrderBook getOrderBook() override;
    // 获取最佳买价
    virtual double getBestBidPrice() override;
    // 获取最佳卖价
    virtual double getBestAskPrice() override;
    // 获取最佳买量
    virtual int getBestBidVolume() override;
    // 获取最佳卖量
    virtual int getBestAskVolume() override;
    // 获取最佳买价和最佳卖价之间的价差
    virtual double getSpread() override;
    // 获取最佳买价和最佳卖价之间的价差百分比
    virtual double getSpreadPercentage() override;
    // 获取订单簿深度
    virtual int getDepth() override;
    // 获取订单簿时间
    virtual Timestamp getUpdateTime() override;

};

class CTPILOB : public ILOB
{
public:
    CTPILOB() = default;
    virtual ~CTPILOB() = default;
    // 创建订单簿
    virtual std::unique_ptr<LimitOrderBook> createLimitOrderBook(const std::string& symbol) override;
    // 获取订单簿
    virtual LimitOrderBook* getLimitOrderBook(const std::string& symbol) override;
    // 移除订单簿
    virtual void removeLimitOrderBook(const std::string& symbol) override;
    // 添加订单簿
    virtual void addLimitOrderBook(const std::string& symbol, std::unique_ptr<LimitOrderBook> lob) override;
    
};