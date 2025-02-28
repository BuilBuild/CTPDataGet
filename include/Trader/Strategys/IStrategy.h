/*
 * @Author: LeiJiulong
 * @Date: 2025-02-28 07:42:55
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-28 07:59:59
 * @Description: 
 */
#pragma once

#include "NonCopyAble.h"

#include <string>

typedef struct StrategyConfig
{

} StrategyConfig;

class IStrategy :  public NonCopyable
{
public:
    
    // 行情数据接收
    virtual void OnMarketData() = 0;
    // 发送交易请求
    virtual void SendOrder() = 0;
    // 接收交易回报
    virtual void OnTradeReport() = 0;

    // 查询持仓信息
    virtual void OnPositionReport() = 0;
    // 其他信息查询
    virtual void OnQuery() = 0;
    // 其他信息回报
    virtual void OnQueryReport() = 0;

    // 声明周期管理
    virtual void OnInit() = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;

    // 策略参数配置
    virtual void SetConfig(const StrategyConfig &config) = 0;

public:
    // 策略名称
    std::string strategyName_;
    // 策略ID
    int strategyId_;

};