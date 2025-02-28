/*
 * @Author: LeiJiulong
 * @Date: 2025-02-27 14:21:17
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-28 09:19:00
 * @Description: 
 */

 #include "Trader/MSGHUB/CTPMSGHUB.h"
 #include "protos/MarketData.pb.h"

 #include <iostream>


 CTPMSGHUB::CTPMSGHUB()
 {
    // 行情发布线程
    marketDataPublishThread_ = std::thread(&CTPMSGHUB::PubMarketData, this);
 }

 CTPMSGHUB::~CTPMSGHUB(){}

 void CTPMSGHUB::Init(const MSGHUBConfig& config)
 {
    lob_ = std::make_unique<CTPILOB>();
    // contextMarketPublish_ = std::make_unique<zmq::context_t>(1);
    // socketMarketReceive_ = std::make_unique<zmq::socket_t>(*contextMarketPublish_, zmq::socket_type::sub);
    // socketMarketReceive_->connect(config.MarketDataSubPort);
    // socketMarketReceive_->set(zmq::sockopt::subscribe, "MarketData");
    contextMarketPublish_ = std::make_unique<zmq::context_t>(1);
    socketMarketPublish_ = std::make_unique<zmq::socket_t>(*contextMarketPublish_, zmq::socket_type::pub);
    socketMarketPublish_->bind(config.MarketDataPublishPort);
 }


 void CTPMSGHUB::Start()
 {

 }

 void CTPMSGHUB::Stop()
 {

 }

 void CTPMSGHUB::WriteMarketData(const OrderBook& orderBook)
 {
    std::unique_lock<std::mutex> lock(marketDataQueueMutex_);
    lob_->addOrderBook(orderBook);
    marketDataQueue_.emplace(orderBook);
    marketDataQueueCondition_.notify_one();
 }

 void CTPMSGHUB::SubMarketData()
 {

 }

 void CTPMSGHUB::PubMarketData()
 {
    while (true)
    {
        std::unique_lock<std::mutex> lock(marketDataQueueMutex_);
        marketDataQueueCondition_.wait(lock, [this] { return !marketDataQueue_.empty(); });
        // 发布数据
        marketDataPub(marketDataQueue_.front());
        marketDataQueue_.pop();
    }
 }

 void CTPMSGHUB::marketDataPub(const OrderBook& orderBook)
 {
    marketdata::MarketData marketData;
    marketData.set_instrumentid(orderBook.InstrumentID);
    marketData.set_lastprice(orderBook.LastPrice);
    marketData.set_askprice1(orderBook.AskPrice1);
    marketData.set_askvolume1(orderBook.AskVolume1);
    marketData.set_bidprice1(orderBook.BidPrice1);
    marketData.set_bidvolume1(orderBook.BidVolume1);
    marketData.set_tradingday(orderBook.TradingDay);
    marketData.set_updatetime(orderBook.UpdateTime);
    marketData.set_turnover(orderBook.Turnover);
    marketData.set_volume(orderBook.Volume);
    marketData.set_openinterest(orderBook.OpenInterest);
    std::string topic = "MarketData";
    topic = topic + "." + orderBook.InstrumentID;
    std::cout << topic << std::endl;
    zmq::message_t messageTopic(topic.data(), topic.size());
    socketMarketPublish_->send(messageTopic,zmq::send_flags::sndmore);
    std::string marketDataStr = marketData.SerializeAsString();
    socketMarketPublish_->send(zmq::buffer(marketDataStr.c_str(), marketDataStr.size()), zmq::send_flags::none);

 }
