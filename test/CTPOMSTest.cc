/*
 * @Author: LeiJiulong
 * @Date: 2025-02-27 12:53:38
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-01 08:47:07
 * @Description: 
 */
#include "Trader/OMS/CTPOMS.h"
#include "protos/MarketData.pb.h"

int main()
{
    OMSConfig omsConfig;
    // 行情订阅地址
    omsConfig.MarketSubAddress = "tcp://localhost:5556";
    // 订单请求地址
    omsConfig.OrderRequestAddress = "tcp://*:5557";

    CTPOMS oms(omsConfig);

    // CTPOMS oms;
    // oms.init("ctp_oms.cfg");
    // oms.run();
    // return 0;
}