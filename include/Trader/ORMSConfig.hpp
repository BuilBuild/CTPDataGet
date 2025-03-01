/*
 * @Author: LeiJiulong
 * @Date: 2025-02-27 08:07:57
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-01 07:47:00
 * @Description: 
 */
#pragma once

#include <string>

// OMS_RMS配置
class ORMSConfig
{
public:
    std::string MarketSubAddress;           // 订阅行情地址
    std::string OrderRequestAddress;        // 订单请求地址
};