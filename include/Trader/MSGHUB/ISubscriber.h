/*
 * @Author: LeiJiulong
 * @Date: 2025-03-01 16:08:19
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-01 16:14:29
 * @Description: 
 */
#pragma once

#include "MarketData/BaseType.hpp"
#include "NonCopyAble.hpp"

// 订阅者接口
class ISubscriber : public NonCopyAble
{
    // 订阅订单簿
    virtual void orderBookWrite (const OrderBook& OrderBook) = 0;
};
