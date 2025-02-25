/*
 * @Author: LeiJiulong
 * @Date: 2025-02-25 11:15:26
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-25 11:18:40
 * @Description:
 */
#include "Trader/EMS/CTPEMS.h"

CTPEMS::CTPEMS() {}
// 初始化
void CTPEMS::initialize(const EMSConfig &config){}
// 启动
void CTPEMS::start(){}
// 停止
void CTPEMS::stop() {}
// 添加执行算法
void CTPEMS::addExecutionAlgorithm(const std::string &symbol, std::unique_ptr<ExecutionAlgorithm> algo) {}
// 移除执行算法
void CTPEMS::removeExecutionAlgorithm(const std::string &symbol) {}
// 添加市场数据处理器
void CTPEMS::addMarketDataHandler(const std::string &symbol, std::unique_ptr<MarketDataHandler> handler) {}
// 移除市场数据处理器
void CTPEMS::removeMarketDataHandler(const std::string &symbol) {}
// 添加风控事件处理器
//  void addRiskEventHandler(const std::string& symbol, std::unique_ptr<RiskEventHandler> handler) {}
// 移除风控事件处理器
 void CTPEMS::removeRiskEventHandler(const std::string &symbol) {}
// 添加动态调整参数处理器
//  void addDynamicAdjustmentHandler(const std::string& symbol, std::unique_ptr<DynamicAdjustmentHandler> handler) {}
// 移除动态调整参数处理器
 void CTPEMS::removeDynamicAdjustmentHandler(const std::string &symbol) {}
// 添加执行报告处理器
//  void addExecutionReportHandler(const std::string& symbol, std::unique_ptr<ExecutionReportHandler> handler) {}
// 移除执行报告处理器
void CTPEMS::removeExecutionReportHandler(const std::string &symbol) {}
// 添加订单转换器
//  void addOrderConverterFactory(const std::string& symbol, std::unique_ptr<OrderConverterFactory> converter) {}
// 移除订单转换器
void CTPEMS::removeOrderConverterFactory(const std::string &symbol) {}
// 添加订单簿
void CTPEMS::addLimitOrderBook(const std::string &symbol, std::unique_ptr<LimitOrderBook> lob) {}
// 移除订单簿
void CTPEMS::removeLimitOrderBook(const std::string &symbol) {}