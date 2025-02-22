/*
 * @Author: LeiJiulong
 * @Date: 2025-02-18 20:21:08
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-18 20:22:20
 * @Description: 
 */
#pragma once

#include <sys/types.h>

#include "CTP/ThostFtdcUserApiStruct.h"

// 交易目标类型
enum TargetType
{
    futures=0,
    stock
};


using OrderBookElement = CThostFtdcDepthMarketDataField;
using OrderBook = CThostFtdcDepthMarketDataField;

// /**
//  * @brief 每次更新的数据基础元素
//  */
// typedef struct OrderBookElement
// {
//     char TargeName[128];
//     int64_t UpdateTime;
//     TargetType OType;
// 	/// 交易日
// 	char TradingDay[9];
// 	/// 合约代码
// 	char InstrumentID[31];
// 	/// 交易所代码
// 	char ExchangeID[9];
// 	/// 最新价格
// 	double LastPrice;
// 	/// 上次结算价
// 	double PreSettlementPrice;
// 	/// 数量
// 	int Volume;
// 	// 持仓量
// 	double OpenInterest;
//     ///申买价一
//     double	BidPrice1;
// 	///申买量一
// 	int	BidVolume1;
// 	///申卖价一
// 	double	AskPrice1;
// 	///申卖量一
// 	int	AskVolume1;
// 	///申买价二
// 	double	BidPrice2;
// 	///申买量二
// 	int	BidVolume2;
// 	///申卖价二
// 	double	AskPrice2;
// 	///申卖量二
// 	int	AskVolume2;
// 	///申买价三
// 	double	BidPrice3;
// 	///申买量三
// 	int	BidVolume3;
// 	///申卖价三
// 	double AskPrice3;
// 	///申卖量三
// 	int	AskVolume3;
// 	///申买价四
// 	double	BidPrice4;
// 	///申买量四
// 	int	BidVolume4;
// 	///申卖价四
// 	double	AskPrice4;
// 	///申卖量四
// 	int	AskVolume4;
// 	///申买价五
// 	double	BidPrice5;
// 	///申买量五
// 	int	BidVolume5;
// 	///申卖价五
// 	double	AskPrice5;
// 	///申卖量五
// 	int	AskVolume5;
//     // 外部回调指针
//     // void* MsgHandle;
// } OrderBook;