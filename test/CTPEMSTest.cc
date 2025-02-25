/*
 * @Author: LeiJiulong
 * @Date: 2025-02-25 11:33:09
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-25 12:39:01
 * @Description: 
 */
#include "Trader/EMS/CTPTraderApiExecutor.h"
#include "Trader/EMS/CTPEMS.h"

#include "MarketData/CTPMarketData.h"
#include "Trader/LOB/CTPLOB.h"


#include <memory>

int main(int argc, char* argv[])
{
    char configPath[128]{};
    if(argc>1)
    {
        sprintf(configPath, "%s", argv[1]);
    }
    else
    {
        sprintf(configPath, "%s", "/home/leijiulong/temp/CTPDataGet/config.ini");
    }

    CTPConfig config(configPath);
    CTPMarketDataAdapter cad;
    std::shared_ptr<CTPILOB> ilob = std::make_shared<CTPILOB>();

    cad.set_callback(std::bind(&CTPILOB::addOrderBook, ilob, std::placeholders::_1));
    cad.connect(&config);
    cad.subscribe(config.getInstrumentId());

    CTPEMS ems;
    // 添加CTP交易执行器
    auto executor = std::make_unique<CTPTraderApiExecutor>("/home/leijiulong/temp/CTPDataGet/CTP.ini");
    ems.addExecutor("ctp",std::move(executor));

    ems.addILOB(ilob);

    getchar();
    // 查询账号资金

    getchar();
    return 0;

}

