/*
 * @Author: LeiJiulong
 * @Date: 2025-02-20 10:15:57
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-21 14:18:38
 * @Description: 
 */
#pragma once

#include "DataWriter.h"
#include "MarketData/Config.h"

#include <thread>
#include <tbb/concurrent_queue.h>
#include <questdb/ingress/line_sender.hpp>
#include <mutex>
#include <memory>
#include <queue>


using WriteQueue = tbb::concurrent_bounded_queue<OrderBook>;
using QuestDBSender = questdb::ingress::line_sender;


/***
 * 连接池配置
 */
typedef struct QuestDBPoolConfig
{
    char userName_[16];
    char passWord_[16];
    char addr_[32];
    int maxPoolSize_;
    int minPoolSize_;

} QuestDBPoolConfig;



/**
 * QuestDB数据库连接池
 */
class QuestDBConnectionPool
{
public:
    QuestDBConnectionPool(const QuestDBConnectionPool&) = delete;
    QuestDBConnectionPool& operator =(const QuestDBConnectionPool&) = delete;

    static QuestDBConnectionPool* GetInstance();
    static void loadConfig(const QuestDBPoolConfig&);
private:
    QuestDBConnectionPool();
    std::queue<std::shared_ptr<QuestDBSender>> senderQueue_;
    
    static QuestDBConnectionPool* questDBConnectionPool_;

    static std::once_flag flag_;
    static std::string addr_;
    static std::string userName_;
    static std::string passWord_;
    static int maxPoolSize_;
    static int initPoolSize_;
};


class DataWriteQuestDB : public WriterAdaptee
{
public:
    DataWriteQuestDB() = delete;
    DataWriteQuestDB(const std::string &conf);
    void specificWrite(const OrderBook&) override;
    ~DataWriteQuestDB();

private:
    void writeDB(const OrderBook &);
private:
    std::string qConf_;
    std::string authorString_;
    std::thread writeThread_;
    WriteQueue writeQueue_;
    questdb::ingress::line_sender sender_;
};