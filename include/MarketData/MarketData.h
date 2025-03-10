/*
 * @Author: LeiJiulong
 * @Date: 2025-02-18 20:24:08
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-21 14:16:49
 * @Description: 
 */
#pragma once

#include <string>
#include <vector>
#include <functional>
#include <condition_variable>
#include <mutex>

#include "BaseType.hpp"
#include "Config.h"

using MarketDataCallback = std::function<void(const OrderBookElement&)>;

class MarketDataAdapter 
{
public:
    virtual void connect(Config* config) = 0;
    virtual void subscribe(const std::vector<std::string>& symbols) = 0;
    virtual void set_callback(MarketDataCallback cb) = 0;
    virtual void disconnect() = 0;
    // 支持心跳检测、重连等基础方法
protected:
    Config* config;
    
    std::condition_variable cv;     // 用于判断是否连接并登录成功
    std::mutex connectMtx_;
    bool loginFlag = false;         // 共享条件变量
};