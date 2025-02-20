/*
 * @Author: LeiJiulong
 * @Date: 2025-02-18 23:22:09
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-20 12:54:55
 * @Description: 
 */
#include <iostream>
#include "MarketData/CTPConfig.h"
#include "MarketData/CTPMarketData.h"
#include "MarketData/DataWriteFile.h"
#include "MarketData/DataWriterAdapter.h"
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
    // 初始化一个适配器对象
    DataWriteFile dw;
    WriterAdapter da(&dw);
    auto iniPtr = config.getIniPtr();
    const char* csvPath = iniPtr->GetValue("CSV", "CSVOutPutPath");
    // 设置文件写入路径
    dw.setFileDirPath(csvPath);
    
    cad.connect(&config);
    // 添加写入回调
    cad.set_callback(std::bind(&WriterAdapter::toWrite, &da, std::placeholders::_1));
    // 订阅标的
    cad.subscribe(config.getInstrumentId());
    

    return 0;
}