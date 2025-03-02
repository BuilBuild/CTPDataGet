/*
 * @Author: LeiJiulong
 * @Date: 2025-03-01 16:12:25
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-02 11:02:22
 * @Description: 
 */
#include "ISubscriber.h"

#include <iostream>
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <atomic>
#include <memory>
#include <questdb/ingress/line_sender.hpp>

// QuestDB配置
typedef struct QuestDBSubscriberConfig final
{
    std::string host;
    std::string username;
    std::string password;
    std::string token;
    std::string database;
    size_t maxPoolSize;
    size_t minPoolSize;
    
} QuestDBSubscriberConfig;

class QuestSenderPool : NonCopyAble
{
public:
    QuestSenderPool() = delete;
    explicit QuestSenderPool(const QuestDBSubscriberConfig& config);
    ~QuestSenderPool();
    questdb::ingress::line_sender getSender();
    void releaseSender(questdb::ingress::line_sender &&sender);
    
private:
    // 创建sender
    questdb::ingress::line_sender createSender();

private:
    // ------ QuestDB Pool配置 -------
    const QuestDBSubscriberConfig  config_;             // QuestDB配置
    std::string host_;                                  // QuestDB地址
    unsigned short port_;                               // QuestDB端口
    std::string authToken_;                             // QuestDB认证token
    size_t maxPoolSize_;                                // QuestDB连接池最大连接数
    std::queue<questdb::ingress::line_sender> pool_;    // QuestDB连接池
    std::mutex mutex_;                                  // QuestDB连接池互斥锁  
    std::condition_variable cv_;                        // QuestDB连接池条件变量
    std::atomic<size_t> activeCount_;                   // QuestDB连接池活跃连接数
};

// QuestDB订阅者
class QuestDBSubscriberWriter : public ISubscriber
{
public:
    QuestDBSubscriberWriter() = delete;
    explicit QuestDBSubscriberWriter(const QuestDBSubscriberConfig& config);
    virtual ~QuestDBSubscriberWriter();
    virtual void orderBookWrite (const OrderBook& orderBook) override;
private:
    // 写入数据库
    void writeOrderBookToDB();
    void writeOrderBook(const OrderBook& orderBook);
    
private:
    QuestDBSubscriberConfig  config_;                       // QuestDB配置
    std::unique_ptr<QuestSenderPool> questSenderPoolPtr_;   // QuestDB连接池
    std::queue<OrderBook> orderBookQueue_;                  // OrderBook队列
    std::mutex orderBookQueueMutex_;                        // OrderBook队列互斥锁
    std::condition_variable orderBookQueueCV_;              // OrderBook队列条件变量
    std::thread writerThread_;                              // 写入数据库线程
};
