/*
 * @Author: LeiJiulong
 * @Date: 2025-02-27 13:15:12
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-27 15:46:47
 * @Description: 
 */
#pragma once

#include "NonCopyAble.hpp"

#include <string>

typedef struct MSGHUBConifg
{
    std::string MarketDataSubPort;
    std::string MarketDataPublishPort;
    std::string DataBasePort;
} MSGHUBConfig;

class IMSGHUB : public NonCopyAble
{
public:
    virtual void Init(const MSGHUBConfig& config) = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void WriteMarketData(const OrderBook& orderBook) override = 0;
protected:
    virtual void SubMarketData() = 0;
    virtual void PubMarketData() = 0;
};
