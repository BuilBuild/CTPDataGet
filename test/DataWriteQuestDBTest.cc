/*
 * @Author: LeiJiulong
 * @Date: 2025-02-20 11:00:22
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-21 11:04:37
 * @Description: 
 */
#include "MarketData/DataWriteQuestDB.h"
#include "MarketData/Config.h"

#include <iostream>

int main(int argc, char* argv[])
{
    // DataWriteQuestDB
    Config config("/home/leijiulong/temp/CTPDataGet/config.ini");
    std::string conf = config.getIniPtr()->GetValue("questDBConfig","conf");
    std::cout << conf << std::endl;
    DataWriteQuestDB dataWriteQuestDB(conf);
    
    // // // dataWriteQuestDB.specificWrite()
    for (int i = 0; i< 5; ++i)
    {
        // YYYYMMDD HH:mm:ss.fff
        OrderBook ob{};
        memcpy(ob.InstrumentID, "aaaaa", 5);
        memcpy(ob.TradingDay, "20240506", 8);
        memcpy(ob.UpdateTime, "08:30:12", 8);
        ob.UpdateMillisec = 500;
        dataWriteQuestDB.specificWrite(ob);
        // data
    }

    // std::cout << "quest db" << std::endl;
    // return 0;
}