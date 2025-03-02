/*
 * @Author: LeiJiulong
 * @Date: 2025-02-21 17:33:31
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-02 11:57:45
 * @Description: 
 */
#include <iostream>
#include "MarketData/CTPConfig.h"
#include "MarketData/CTPMarketData.h"
#include "MarketData/DataWriteFile.h"
#include "MarketData/DataWriterAdapter.h"
#include "MarketData/DataWriteQuestDB.h"

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
    CTPMarketDataAdapter marketDataAdapter;
    // 初始化一个适配器对象
    DataWriteFile dataWriteFile;
    auto iniPtr = config.getIniPtr();
    const char* csvPath = iniPtr->GetValue("CSV", "CSVOutPutPath");
    // 设置文件写入路径
    dataWriteFile.setFileDirPath(csvPath);
    // 生成一个写入适配
    WriterAdapter adapter01(&dataWriteFile);
    
    // 添加写入回调
    marketDataAdapter.set_callback(std::bind(&WriterAdapter::toWrite, &adapter01, std::placeholders::_1));
    
    // 再重新设置一个适配器，添加一个写入数据库的对象，并注册回调
    std::string qConf = config.getIniPtr()->GetValue("questDBConfig","conf");
    DataWriteQuestDB dataWriteQuestDB(qConf);
    WriterAdapter da2(&dataWriteQuestDB);
    marketDataAdapter.set_callback(std::bind(&WriterAdapter::toWrite, &da2,std::placeholders::_1));

    // 配置数据接收中心并开始连接
    marketDataAdapter.connect(&config);
    //  订阅标的
    marketDataAdapter.subscribe(config.getInstrumentId());
    
    return 0;
}