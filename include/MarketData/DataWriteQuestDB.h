/*
 * @Author: LeiJiulong
 * @Date: 2025-02-20 10:15:57
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-20 11:21:28
 * @Description: 
 */
#pragma once

#include "DataWriter.h"
#include "MarketData/Config.h"

#include <thread>
#include <mutex>
#include <tbb/concurrent_queue.h>
#include <string>

class DataWriteQuestDB : public WriterAdaptee
{
public:
    DataWriteQuestDB() = delete;
    DataWriteQuestDB(Config *);
    void specificWrite(const OrderBook&) override;
private:
    std::string authorString_;
};