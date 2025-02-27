/*
 * @Author: LeiJiulong
 * @Date: 2025-02-27 15:57:34
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-27 18:59:41
 * @Description: 
 */
#include "Trader/MSGHUB/CTPMSGHUB.h"
#include "MarketData/CTPMarketData.h"

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
    MSGHUBConfig mcfg{};
    mcfg.MarketDataPublishPort = "tcp://*:5556";
    mcfg.MarketDataSubPort = "tcp://localhost:5557";
    CTPMSGHUB ctpmsghub;

    ctpmsghub.Init(mcfg);
    
    CTPConfig config(configPath);
    CTPMarketDataAdapter cad;
    cad.set_callback(std::bind(&CTPMSGHUB::WriteMarketData, &ctpmsghub, std::placeholders::_1));
    cad.connect(&config);
    
    


    cad.subscribe(config.getInstrumentId());

    return 0;

}
