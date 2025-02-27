/*
 * @Author: LeiJiulong
 * @Date: 2025-02-27 12:53:38
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-27 12:53:40
 * @Description: 
 */
#include "Trader/OMS/CTPOMS.h"
#include "protos/MarketData.pb.h"

int main()
{
    OMSConfig omsConfig;
    omsConfig.MarketSubAddress = "tcp://localhost:5556";

    CTPOMS oms(omsConfig);

    // CTPOMS oms;
    // oms.init("ctp_oms.cfg");
    // oms.run();
    // return 0;
}