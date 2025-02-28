/*
 * @Author: LeiJiulong
 * @Date: 2025-02-28 08:08:18
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-28 08:09:40
 * @Description: 
 */
#pragma once

#include "IStrategy.h"

#include <zmq.hpp>

class ICTPStrategy : public IStrategy
{
public:
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

    // 策略参数配置
    virtual void SetConfig(const StrategyConfig &config) override;
protected:
    // 策略配置

};


