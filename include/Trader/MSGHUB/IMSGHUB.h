/*
 * @Author: LeiJiulong
 * @Date: 2025-02-27 13:15:12
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-01 08:48:12
 * @Description: 
 */
#pragma once

#include "NonCopyAble.hpp"
#include "MarketData/BaseType.hpp"

#include <string>

typedef struct MSGHUBConifg
{
    std::string MarketDataSubPort;  // 订阅行情数据端口
    std::string MarketDataPublishPort; // 发布行情数据端口
    std::string DataBasePort;           // 数据库端口
} MSGHUBConfig;

class IMSGHUB : public NonCopyAble
{
public:
    virtual void Init(const MSGHUBConfig& config) = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void WriteMarketData(const OrderBook& orderBook) = 0;
protected:
    virtual void SubMarketData() = 0;
    virtual void PubMarketData() = 0;
};
