/*
 * @Author: LeiJiulong
 * @Date: 2025-02-18 23:22:09
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-20 08:19:29
 * @Description: 
 */
#include <iostream>
#include "MarketData/CTPConfig.h"
#include "MarketData/CTPMarketData.h"
#include "MarketData/DataWriteFile.h"
#include "MarketData/DataWriterAdapter.h"
#include <functional>

int main()
{
    CTPConfig config("/home/leijiulong/temp/CTPDataGet/config.ini");
    CTPMarketDataAdapter cad;
    // 初始化一个适配器对象
    DataWriteFile dw;
    WriterAdapter da(&dw);
    // 设置文件写入路径
    dw.setFileDirPath("/home/leijiulong/temp/CTPDataGet/DataStore/CSV");
    
    cad.connect(&config);
    // 添加写入回调
    cad.set_callback(std::bind(&WriterAdapter::toWrite, &da, std::placeholders::_1));
    // 订阅标的
    cad.subscribe(config.getInstrumentId());
    

    return 0;
}