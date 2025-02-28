/*
 * @Author: LeiJiulong
 * @Date: 2025-02-28 08:08:18
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-28 14:29:56
 * @Description: 
 */
#pragma once

#include "IStrategy.h"

#include <zmq.hpp>
#include <memory>
#include <thread>

typedef struct ICTPStrategyConfig 
{
    // 订阅合约
    std::vector<std::string> instruments_;
    // 订阅地址
    std::string subAddr_;
} ICTPStrategyConfig;

class ICTPStrategy : public IStrategy
{
public:
    ICTPStrategy() = delete;
    explicit ICTPStrategy(const ICTPStrategyConfig& config);
    virtual ~ICTPStrategy();
    // 行情数据接收
    virtual void OnMarketData() override;
    // 发送交易请求
    virtual void SendOrder() override;
    // 接收交易回报
    virtual void OnTradeReport() override;

    // 查询持仓信息
    virtual void OnPositionReport() override;
    // 其他信息查询
    virtual void OnQuery() override;
    // 其他信息回报
    virtual void OnQueryReport() override;

    // 生命周期管理
    virtual void OnInit() override;
    virtual void Start() override;
    virtual void Stop() override;
    
    // 订阅行情数据
    virtual void subscribeMarketData(const std::string &instrument);
    // 取消订阅行情数据
    virtual void unsubscribeMarketData(const std::string &instrument);

    // 策略参数配置
    virtual void SetConfig(const StrategyConfig &config) override;

protected:
    // 策略配置
    StrategyConfig strategyConfig_;
    // zmq上下文
    zmq::context_t context_;
    // 行情数据接收
    zmq::socket_t marketDataSubscribe_;
    // 行情处理线程
    std::thread marketDataThread_;

};


