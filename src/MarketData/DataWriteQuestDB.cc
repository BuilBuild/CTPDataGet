/*
 * @Author: LeiJiulong
 * @Date: 2025-02-20 10:20:14
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-21 14:49:49
 * @Description:
 */
#include "MarketData/DataWriteQuestDB.h"
#include "MarketData/Utils.hpp"

#include <spdlog/spdlog.h>
#include <chrono>


// #include ""


QuestDBConnectionPool* QuestDBConnectionPool::questDBConnectionPool_=nullptr;
std::once_flag QuestDBConnectionPool::flag_{};
std::string QuestDBConnectionPool::addr_{};
std::string QuestDBConnectionPool::userName_{};
std::string QuestDBConnectionPool::passWord_{};
int QuestDBConnectionPool::maxPoolSize_{};
int QuestDBConnectionPool::initPoolSize_{};

QuestDBConnectionPool* QuestDBConnectionPool::GetInstance()
{
    std::call_once(flag_, [&]{
        questDBConnectionPool_ = new QuestDBConnectionPool;
    });
    return questDBConnectionPool_;
}
void QuestDBConnectionPool::loadConfig(const QuestDBPoolConfig& config)
{
    userName_ = config.userName_;
    passWord_ = config.passWord_;
    addr_= config.passWord_;
    maxPoolSize_ = config.maxPoolSize_;
    initPoolSize_ = config.minPoolSize_;
}

QuestDBConnectionPool::QuestDBConnectionPool()
{
    for(int i=0; i< initPoolSize_; ++i)
    {
        char conf[128]{};
        sprintf(conf, "https::addr=%s;username=%s;password=%s;", addr_.c_str(), userName_.c_str(), passWord_.c_str());
        // 一次只能一个线程
        auto sender = questdb::ingress::line_sender::from_conf(conf);
        
    }
}

DataWriteQuestDB::DataWriteQuestDB(const std::string &conf)
: qConf_(conf),sender_(
    questdb::ingress::line_sender::from_conf(
        questdb::ingress::utf8_view{qConf_.c_str(), qConf_.size()}))
{
    writeThread_ = std::thread([this]{
        while (true)
        {
            OrderBook ob{};
            writeQueue_.pop(ob);
            writeDB(ob);
        }
    });
}

void DataWriteQuestDB::specificWrite(const OrderBook &ob)
{
    writeQueue_.emplace(ob);
}

DataWriteQuestDB::~DataWriteQuestDB()
{
    if(writeThread_.joinable())
    {
        writeThread_.join();
    }
}

void DataWriteQuestDB::writeDB(const OrderBook &ob)
{   
    questdb::ingress::line_sender_buffer buffer;
    buffer.table("FutureTest")
    .symbol("FutureID", std::string_view{ob.InstrumentID, strlen(ob.InstrumentID)})
    .column("LastPrice", ob.LastPrice).column("Volume", (int64_t)ob.Volume);

    buffer.column("BidPrice1", ob.BidPrice1).column("BidVolume1", (int64_t)ob.BidVolume1);
    // buffer.column("BidPrice2", ob.BidPrice2).column("BidVolume2", (int64_t)ob.BidVolume2);
    // buffer.column("BidPrice3", ob.BidPrice3).column("BidVolume3", (int64_t)ob.BidVolume3);
    // buffer.column("BidPrice4", ob.BidPrice4).column("BidVolume4", (int64_t)ob.BidVolume4);
    // buffer.column("BidPrice5", ob.BidPrice5).column("BidVolume5", (int64_t)ob.BidVolume5);
    buffer.column("AskPrice1", ob.AskPrice1).column("AskVolume1",(int64_t)ob.AskVolume1); 
    char t[22]{};
    sprintf(t, "%s %s.%d", ob.TradingDay, ob.UpdateTime, ob.UpdateMillisec);
    auto tk = self_time_mk::ConvertToTimestamp(t);
    auto tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(std::chrono::milliseconds(tk));
    buffer.column("UpdateTime", tk);
    buffer.at(questdb::ingress::timestamp_nanos::now());
    
    sender_.flush(buffer);
}