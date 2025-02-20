/*
 * @Author: LeiJiulong
 * @Date: 2025-02-20 11:00:22
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-20 11:07:46
 * @Description: 
 */
#include "MarketData/DataWriteQuestDB.h"
#include "MarketData/Config.h"

#include <iostream>

int main()
{
    // DataWriteQuestDB
    Config config("/home/leijiulong/temp/CTPDataGet/config.ini");
    DataWriteQuestDB dataWriteQuestDB(&config);

    // dataWriteQuestDB.specificWrite()
    for (int i = 0; i< 5; ++i)
    {
        OrderBook ob;
        dataWriteQuestDB.specificWrite(ob);
        // data
    }

    std::cout << "quest db" << std::endl;
    return 0;
}