/*
 * @Author: LeiJiulong
 * @Date: 2025-02-20 10:20:14
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-02 11:17:33
 * @Description:
 */

#include "Trader/MSGHUB/QuestDBSubscriberWriter.h"

#include <sstream>
#include <cstring>



QuestSenderPool::QuestSenderPool(const QuestDBSubscriberConfig& config) : config_(config)
{
    for(int i = 0; i < config_.minPoolSize; ++i)
    {
        std::cout << "QuestSenderPool::QuestSenderPool " << i << std::endl;
        pool_.push(std::move(createSender()));
    }
    
}

QuestSenderPool::~QuestSenderPool()
{}

questdb::ingress::line_sender QuestSenderPool::getSender()
{
    std::unique_lock <std::mutex> lock(mutex_);
    cv_.wait(lock, [this] { return !pool_.empty() || activeCount_< config_.maxPoolSize;});
    if(!pool_.empty())
    {
        auto sender = std::move(pool_.front());
        pool_.pop();
        return sender;
    }
    // 如果池为空但未达上限
    activeCount_++;
    return createSender();
}

void QuestSenderPool::releaseSender(questdb::ingress::line_sender &&sender)
{
    std::unique_lock <std::mutex> lock(mutex_);
    pool_.push(std::move(sender));
    activeCount_--;
    cv_.notify_one();
}


questdb::ingress::line_sender QuestSenderPool::createSender()
{
    std::ostringstream oss;
    oss << "http::addr=" << config_.host << ";username=" << config_.username << ";password=" << config_.password << ";";
    std::string confUrl = oss.str();
    return questdb::ingress::line_sender::from_conf(questdb::ingress::utf8_view{confUrl.c_str(), confUrl.size()});
} 

QuestDBSubscriberWriter::QuestDBSubscriberWriter(const QuestDBSubscriberConfig& config)
    : config_(config), questSenderPoolPtr_(new QuestSenderPool(config))
{
    writerThread_ = std::thread(&QuestDBSubscriberWriter::writeOrderBookToDB, this);
}

QuestDBSubscriberWriter::~QuestDBSubscriberWriter()
{
    if (writerThread_.joinable())
    {
        writerThread_.join();
    }
    
}

void QuestDBSubscriberWriter::orderBookWrite (const OrderBook& orderBook)
{
    // std::cout << "QuestDBSubscriberWriter::orderBookWrite" << std::endl;
    // questSenderPoolPtr_->getSender();
    std::unique_lock <std::mutex> lock(orderBookQueueMutex_);
    orderBookQueue_.emplace(orderBook);
}

void QuestDBSubscriberWriter::writeOrderBookToDB()
{
    while (true)
    {
        std::unique_lock <std::mutex> lock(orderBookQueueMutex_);
        orderBookQueueCV_.wait(lock, [this] { return !orderBookQueue_.empty(); });
        auto orderBook = std::move(orderBookQueue_.front());
        writeOrderBook(orderBook);
        orderBookQueue_.pop();
    } 
}

void QuestDBSubscriberWriter::writeOrderBook(const OrderBook& orderBook)
{
    std::cout << orderBook.InstrumentID << std::endl;
    auto sender =  questSenderPoolPtr_->getSender();
    questdb::ingress::line_sender_buffer buffer;
    buffer.table("FutureTest1")
    .symbol("FutureID", std::string_view{orderBook.InstrumentID, strlen(orderBook.InstrumentID)})
    .column("LastPrice", orderBook.LastPrice).column("Volume", (int64_t)orderBook.Volume);

    buffer.column("BidPrice1", orderBook.BidPrice1).column("BidVolume1", (int64_t)orderBook.BidVolume1);
    buffer.column("BidPrice5", orderBook.BidPrice5).column("BidVolume5", (int64_t)orderBook.BidVolume5);
    buffer.column("AskPrice1", orderBook.AskPrice1).column("AskVolume1",(int64_t)orderBook.AskVolume1); 
    char t[22]{};
    sprintf(t, "%s %s.%d", orderBook.TradingDay, orderBook.UpdateTime, orderBook.UpdateMillisec);
    // auto tk = self_time_mk::ConvertToTimestamp(t);
    // auto tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(std::chrono::milliseconds(tk));
    // buffer.column("UpdateTime", tk);
    buffer.at(questdb::ingress::timestamp_nanos::now());

    sender.flush(buffer);
    questSenderPoolPtr_->releaseSender(std::move(sender));
}