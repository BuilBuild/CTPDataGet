/*
 * @Author: LeiJiulong
 * @Date: 2025-02-28 08:10:34
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-28 08:22:34
 * @Description: 
 */

#include "Trader/Strategys/ICTPStrategy.h"


// 行情数据接收
 void ICTPStrategy::OnMarketData() {}
// 发送交易请求
 void ICTPStrategy::SendOrder() {}
// 接收交易回报
 void ICTPStrategy::OnTradeReport() {}

// 查询持仓信息
 void ICTPStrategy::OnPositionReport() {}
// 其他信息查询
 void ICTPStrategy::OnQuery() {}
// 其他信息回报
 void ICTPStrategy::OnQueryReport() {}

// 生命周期管理
 void ICTPStrategy::OnInit() {}
 void ICTPStrategy::Start() {}
 void ICTPStrategy::Stop() {}

// 策略参数配置
 void ICTPStrategy::SetConfig(const StrategyConfig &config) {}
