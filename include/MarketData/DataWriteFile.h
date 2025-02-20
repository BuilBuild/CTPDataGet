/*
 * @Author: LeiJiulong
 * @Date: 2025-02-20 03:48:35
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-20 05:16:59
 * @Description: 
 */
#pragma once

#include "DataWriter.h"
#include <thread>
#include <mutex>
#include <tbb/concurrent_queue.h>
#include <string>

using WriteQueue = tbb::concurrent_bounded_queue<OrderBook>;


class DataWriteFile : public WriterAdaptee
{
public:
    DataWriteFile();

    virtual ~DataWriteFile();
    void specificWrite(const OrderBook&) override;
    void setFileDirPath(std::string);
private:
    void writeFile(OrderBook &);
    bool fileExist(std::string &);
private:
    bool stop = false;
    std::string fileDirPath_{};
    WriteQueue writeQueue_;
    std::thread writeThread_;
    std::mutex stopMtx_;
};


