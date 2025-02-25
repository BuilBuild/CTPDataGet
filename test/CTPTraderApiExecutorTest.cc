/*
 * @Author: LeiJiulong
 * @Date: 2025-02-23 00:48:18
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-25 00:51:04
 * @Description: 
 */
#include "Trader/EMS/CTPTraderApiExecutor.h"

#include <string>
#include <iostream>

int main()
{
    CTPTraderApiExecutor executor("/home/leijiulong/temp/CTPDataGet/CTP.ini");
    getchar();
    // 查询账号资金
    executor.reqQueryTradingAccount();
    // OrderRequest orderReq;
    // orderReq.orderId = "123";
    // orderReq.symbol = "000001";
    // orderReq.side = OrderSide::Buy;
    // orderReq.price = 10.0;
    // orderReq.quantity = 100;
    // orderReq.type = OrderType::Limit;
    // TimeRange validTime;
    // validTime.type = TimeRangeType::ABSOLUTE_TIME;
    // validTime.startTime = std::chrono::system_clock::now();
    // validTime.endTime = std::chrono::system_clock::now();
    // orderReq.validTime = validTime;
    // executor.execute(orderReq);
    getchar();
    OrderRequest orderReq;
    orderReq.orderId = "123";
    orderReq.symbol = "000001";
    orderReq.side = OrderSide::Buy;
    orderReq.price = 10.0;
    orderReq.quantity = 100;
    orderReq.type = OrderType::Limit;
    TimeRange validTime;
    validTime.type = TimeRangeType::ABSOLUTE_TIME;
    validTime.startTime = std::chrono::system_clock::now();
    validTime.endTime = std::chrono::system_clock::now();
    orderReq.validTime = validTime;
    executor.execute(orderReq);
    getchar();
    return 0;
}