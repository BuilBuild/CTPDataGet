/*
 * @Author: LeiJiulong
 * @Date: 2025-02-25 10:29:18
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-25 11:53:32
 * @Description: 
 */
#pragma once

#include "IEMS.h"
#include "NonCopyAble.hpp"

class CTPEMS : public I_EMS, public NonCopyAble
{
public:
    CTPEMS();
    virtual ~CTPEMS() = default;
    // 初始化
    virtual void initialize(const EMSConfig& config) override;
    // 启动
    virtual void start() override;
    // 停止
    virtual void stop() override;
    // 添加执行算法
    virtual void addExecutionAlgorithm(const std::string& symbol, std::unique_ptr<ExecutionAlgorithm> algo) override;
    // 移除执行算法
    virtual void removeExecutionAlgorithm(const std::string& symbol) override;
    // 添加市场数据处理器
    virtual void addMarketDataHandler(const std::string& symbol, std::unique_ptr<MarketDataHandler> handler) override;
    // 移除市场数据处理器
    virtual void removeMarketDataHandler(const std::string& symbol) override;
    // 移除风控事件处理器
    virtual void removeRiskEventHandler(const std::string& symbol) override;
    // 移除动态调整参数处理器
    virtual void removeDynamicAdjustmentHandler(const std::string& symbol) override;
    // 移除执行报告处理器
    virtual void removeExecutionReportHandler(const std::string& symbol) override;
    // 移除订单转换器
    virtual void removeOrderConverterFactory(const std::string& symbol) override;
    // 添加订单簿
    virtual void addLimitOrderBook(const std::string& symbol, std::unique_ptr<LimitOrderBook> lob) override;
    // 移除订单簿
    virtual void removeLimitOrderBook(const std::string& symbol) override;
    virtual void adjustExecution(const std::string& algoId, const DynamicAdjustment& adj) override {};
    virtual void subscribeMarketData(const std::string& symbol, MarketDataHandler* handler) override {};
    virtual void registerAlgorithm(const std::string& name, std::unique_ptr<ExecutionAlgorithm> algo) override {};
    virtual ExecutionReport generateReport(const std::string& algoId) const override {return ExecutionReport{};};
    virtual std::string scheduleExecution(const OrderRequest& req, const ExecutionStrategyConfig& config) override {return "";};
};

