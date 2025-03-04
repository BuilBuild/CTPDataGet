/*
 * @Author: LeiJiulong
 * @Date: 2025-03-03 07:53:51
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-04 16:47:39
 * @Description: 启动消息中心，用于接收市场行情数据和推送数据，可注册数据写入地址
 */

#include "Trader/MSGHUB/CTPMSGHUB.h"
#include "MarketData/CTPMarketData.h"
#include "Trader/MSGHUB/QuestDBSubscriberWriter.h"


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
    CTPMSGHUB ctpmsghub;
    // 给数据中心注入数据写入其他位置的回调
    // 先初始化一个写入对象
    QuestDBSubscriberConfig qdbconfig{};
    qdbconfig.host = "127.0.0.1:9000";
    qdbconfig.username = "admin";
    qdbconfig.password = "quest";
    qdbconfig.minPoolSize = 2;
    qdbconfig.maxPoolSize = 10;
    QuestDBSubscriberWriter questDBwriter(qdbconfig);
    
    ctpmsghub.RegisterMarketDataCallback(std::bind(&QuestDBSubscriberWriter::orderBookWrite, &questDBwriter, std::placeholders::_1));

    // QuestDBSubscriberWriter qdbw;
    

    ctpmsghub.Init(mcfg);
    
    CTPConfig config(configPath);
    CTPMarketDataAdapter cad;
    // 让通过cad接收到的数据，通过ctpmsghub的回调函数WriteMarketData进行处理
    cad.set_callback(std::bind(&CTPMSGHUB::WriteMarketData, &ctpmsghub, std::placeholders::_1));
    cad.connect(&config);
    // 订阅行情数据
    cad.subscribe(config.getInstrumentId());

    return 0;

}
