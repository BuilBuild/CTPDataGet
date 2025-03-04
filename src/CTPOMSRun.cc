/*
 * @Author: LeiJiulong
 * @Date: 2025-03-03 07:55:38
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-04 16:15:15
 * @Description: 启动订单管理模块，用于管理订单生命周期和订单的执行
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