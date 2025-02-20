/*
 * @Author: LeiJiulong
 * @Date: 2025-02-20 03:52:52
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-20 09:19:21
 * @Description: 
 */
#include "MarketData/DataWriteFile.h"
#include "MarketData/Utils.hpp"

#include <spdlog/spdlog.h>
#include <fstream>
#include <string>

#include <iostream>


DataWriteFile::DataWriteFile()
{
    writeThread_ = std::thread(
        [this]{
            while(true)
            {
                // if(stop && writeQueue_.size() == 0){return;}
                OrderBook ob{};
                // 当队列为空时自动堵塞
                writeQueue_.pop(ob);
                writeFile(ob);
            }
        }
    );
}

void DataWriteFile::writeFile(OrderBook &ob)
{
    std::string filepath = fileDirPath_ + ob.InstrumentID + ".csv";
    auto isFileExist = fileExist(filepath);
    
    if(isFileExist)
    {
        // 如果文件存在
        std::fstream file;
        file.open(filepath, std::ios::out | std::ios::app);
        char t[22]{};
        sprintf(t, "%s %s.%d", ob.TradingDay, ob.UpdateTime, ob.UpdateMillisec);
        
        file << ob.InstrumentID << ","<< ob.ExchangeInstID << "," << self_time_mk::ConvertToTimestamp(t) << ","
            << ob.LastPrice << "," << ob.Volume << ","<< ob.OpenInterest << ","
            << ob.BidPrice1 << "," << ob.BidVolume1 << "," << ob.AskPrice1 << "," << ob.AskVolume1
            // << ob.BidPrice2 << "," << ob.BidVolume2 << "," << ob.AskPrice2 << "," << ob.AskVolume2 << ","
            // << ob.BidPrice3 << "," << ob.BidVolume3 << "," << ob.AskPrice3 << "," << ob.AskVolume3 << ","
            // << ob.BidPrice4 << "," << ob.BidVolume4 << "," << ob.AskPrice4 << "," << ob.AskVolume4 << ","
            // << ob.BidPrice5 << "," << ob.BidVolume5 << "," << ob.AskPrice5 << "," << ob.AskVolume5 
            << '\n';
        file.close();
    }
    else
    {
        // 文件不存在
        std::fstream file;
        file.open(filepath, std::ios::out | std::ios::app);
        file << "TargeName," << "ExchangeInstID," << "UpdateTime," << "LastPrice," << "Volume," << "OpenInterest,"
            << "BidPrice1," << "BidVolume1," << "AskPrice1," << "AskVolume1"
            // << "BidPrice2," << "BidVolume2," << "AskPrice2," << "AskVolume2,"
            // << "BidPrice3," << "BidVolume3," << "AskPrice3," << "AskVolume3,"
            // << "BidPrice4," << "BidVolume4," << "AskPrice4," << "AskVolume4,"
            // << "BidPrice5," << "BidVolume5," << "AskPrice5," << "AskVolume5"
            << '\n';

        char t[22]{};
        sprintf(t, "%s %s.%d", ob.TradingDay, ob.UpdateTime, ob.UpdateMillisec);
        
        file << ob.InstrumentID << ","<< ob.ExchangeInstID << "," << self_time_mk::ConvertToTimestamp(t) << ","
            << ob.LastPrice << "," << ob.Volume << ","<< ob.OpenInterest << ","
            << ob.BidPrice1 << "," << ob.BidVolume1 << "," << ob.AskPrice1 << "," << ob.AskVolume1
            // << ob.BidPrice2 << "," << ob.BidVolume2 << "," << ob.AskPrice2 << "," << ob.AskVolume2 << ","
            // << ob.BidPrice3 << "," << ob.BidVolume3 << "," << ob.AskPrice3 << "," << ob.AskVolume3 << ","
            // << ob.BidPrice4 << "," << ob.BidVolume4 << "," << ob.AskPrice4 << "," << ob.AskVolume4 << ","
            // << ob.BidPrice5 << "," << ob.BidVolume5 << "," << ob.AskPrice5 << "," << ob.AskVolume5 
            << '\n';
            
        file.close();
    }

}

void DataWriteFile::setFileDirPath(std::string filePathDir)
{
    fileDirPath_ = filePathDir;
}

bool DataWriteFile::fileExist(std::string &filePath)
{
    std::ifstream file(filePath);
    auto rt = file.good();
    file.close();
    return rt; 
}

DataWriteFile::~DataWriteFile()
{
    stop = true;
    if(writeThread_.joinable())
    {
        writeThread_.join();
    }
    std::cout << "quit" << std::endl;
}

void DataWriteFile::specificWrite(const OrderBook &ob)
{
    writeQueue_.emplace(ob);
}