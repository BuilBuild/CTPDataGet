/*
 * @Author: LeiJiulong
 * @Date: 2025-02-21 07:31:21
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-21 08:08:15
 * @Description: 
 */

 #include "MarketData/DataWriteQuestDB.h"
 #include "SimpleIni.h"

 #include <iostream>

 int main()
 {
    CSimpleIniA ini;
    auto rs = ini.LoadFile("/home/leijiulong/temp/CTPDataGet/config.ini");
    if(0 == rs)
    {
        std::cout << "load Success" << std::endl;
    }
    else
    {
        exit(-1);
    }

    QuestDBPoolConfig config{};
    sprintf(config.userName_, "%s", ini.GetValue("questDBConfig", "username"));
    sprintf(config.passWord_, "%s", ini.GetValue("questDBConfig", "password"));
    sprintf(config.addr_, "%s", ini.GetValue("questDBConfig", "addr"));
    config.minPoolSize_ = ini.GetLongValue("questDBConfig", "init_pool_size", 0);
    config.maxPoolSize_  = ini.GetLongValue("questDBConfig", "max_pool_size", 0);
    QuestDBConnectionPool::loadConfig(config);
    
    auto c = QuestDBConnectionPool::GetInstance();
    std::cout << c << std::endl;
    std::cout << "quest pool test" << std::endl;
    return 0;
 }
