/*
 * @Author: LeiJiulong
 * @Date: 2025-02-22 21:42:50
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-25 09:46:22
 * @Description: 
 */
#pragma once

#include "TraderBaseType.hpp"
#include "ExecutionContext.hpp"
#include "Trader/LOB/ILOB.h"

#include <string>
#include <memory>

// 执行算法接口
class ExecutionAlgorithm
{
public:
    virtual void initialize(const ExecutionContext& ctx) = 0;                   // 初始化
    virtual OrderSlice generateNextSlice(const ExchangeStatus& state) = 0;      // 生成下一个分片
    virtual void handleRejection(const OrderRejection& rejection) = 0;          // 处理订单拒绝
    virtual ~ExecutionAlgorithm() = default;
};

// 市场数据处理接口
class MarketDataHandler
{
public:
    virtual void onMarketDataUpdate(const MarketDataEvent& event) = 0;
    virtual ~MarketDataHandler() = default;
};

class EMSConfig
{
    // 系统配置
};

// 执行报告
class ExecutionReport
{
    // 报告内容
};

// 风控事件
class RiskEvent
{
    // 风控事件内容
};

// 动态调整参数
class DynamicAdjustment
{
    // 调整参数
};


// 执行管理系统接口
class I_EMS 
{
public:
    //---------- 核心接口 ----------
    // 策略管理
    virtual void registerAlgorithm(const std::string& name, std::unique_ptr<ExecutionAlgorithm> algo) = 0;

    // 执行控制
    virtual std::string scheduleExecution(const OrderRequest& req, const ExecutionStrategyConfig& config) = 0;

    // 动态调整
    virtual void adjustExecution(const std::string& algoId, const DynamicAdjustment& adj) = 0;

    //---------- 市场交互 ----------
    // 市场数据订阅
    virtual void subscribeMarketData(const std::string& symbol, MarketDataHandler* handler) = 0;

    //---------- 监控与反馈 ----------
    // 风控事件订阅
    virtual ExecutionReport generateReport(const std::string& algoId) const = 0;

    //---------- 系统生命周期 ----------
    // 系统初始化
    virtual void initialize(const EMSConfig& config) = 0;
    // 系统关闭   
    virtual void shutdown() = 0;

    virtual ~I_EMS() = default;
    
protected:
    //---------- 内部逻辑钩子 ----------
    // 市场数据驱动决策
    virtual void onMarketDataUpdate(const MarketDataEvent& event){};
    //  风控事件处理
    virtual void onRiskLimitViolated(const RiskEvent& event){};

    //---------- 内部数据 ----------
    std::unique_ptr<ILOB> iLobs_;
};
