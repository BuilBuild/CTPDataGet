/*
 * @Author: LeiJiulong
 * @Date: 2025-02-25 09:56:41
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-25 10:05:22
 * @Description: 
 */
#include "MarketData/CTPMarketData.h"
#include "Trader/LOB/CTPLOB.h"

#include <iostream>
#include <functional>

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
    CTPILOB ilob;
    cad.set_callback(std::bind(&CTPILOB::addOrderBook, &ilob, std::placeholders::_1));
    cad.connect(&config);
    cad.subscribe(config.getInstrumentId());
    // ilob.addOrderBook()
    getchar();
}