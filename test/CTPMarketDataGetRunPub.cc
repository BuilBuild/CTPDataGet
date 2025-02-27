/*
 * @Author: LeiJiulong
 * @Date: 2025-02-27 08:13:56
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-27 12:36:53
 * @Description:
 */
#include "MarketData/CTPConfig.h"
#include "MarketData/CTPMarketData.h"
// include "MarketData/DataWriteFile.h"
#include "MarketData/DataWriterAdapter.h"
#include "MarketData/DataWriteQuestDB.h"

#include "protos/MarketData.pb.h"

#include <iostream>
#include <functional>
#include <zmq.hpp>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>

// 定义一个类的仿函数用于回调
class Publisher
{
public:
    Publisher() : context_(1), socket_(context_, ZMQ_PUB)
    {
        socket_.bind("tcp://*:5556");
        thread_ = std::thread([this]()
                              {
            while (true) {
                std::unique_lock<std::mutex> lock(mutex_);
                condition_.wait(lock, [this]{ 
                    return !dataQueue_.empty(); 
                });
                auto data = dataQueue_.front();
                marketdata::MarketData dataProto;
                dataProto.set_instrumentid(data.InstrumentID);
                dataProto.set_lastprice(data.LastPrice);
                // dataProto.set_las(data.LastPrice);
                std::string serializedData = dataProto.SerializeAsString();
                // MarketData::CTPMarketData::publishData(data, socket_);
                std::cout << "publish data:" << data.InstrumentID << std::endl;
                std::cout << "publish data:" << serializedData << std::endl;
                // // 需要显式构造消息并指定大小
                // zmq::message_t msg(serializedData.size());
                // memcpy(msg.data(), serializedData.data(), serializedData.size());

                // 使用旧版标志宏
                socket_.send(zmq::str_buffer("MarketData"), zmq::send_flags::sndmore);
                socket_.send(zmq::buffer(serializedData.data(), serializedData.size()),
                zmq::send_flags::none);
                dataQueue_.pop();
            } });
    };

    void marketDataReceive(const OrderBookElement &data)
    {
        std::cout << "marketDataReceive" << std::endl;
        std::cout << data.InstrumentID << std::endl;
        std::unique_lock<std::mutex> lock(mutex_);
        dataQueue_.emplace(data);
        condition_.notify_one();
    }
    ~Publisher()
    {
        if (thread_.joinable())
        {
            thread_.join();
        }
    }

private:
    zmq::context_t context_;
    zmq::socket_t socket_;

    // 接收数据的队列
    std::queue<OrderBookElement> dataQueue_;

    // 用于发布数据
    std::thread thread_;
    std::mutex mutex_;
    std::condition_variable condition_;
};

int main(int argc, char *argv[])
{
    char configPath[128]{};
    if (argc > 1)
    {
        sprintf(configPath, "%s", argv[1]);
    }
    else
    {
        sprintf(configPath, "%s", "/home/leijiulong/temp/CTPDataGet/config.ini");
    }
    // 生成CTP配置
    CTPConfig config(configPath);
    CTPMarketDataAdapter cad; // 生成CTP行情数据获取类
    cad.connect(&config);     // 连接行情服务器

    // 创建一个可回调对象写入事件回调
    Publisher pub;
    cad.set_callback(std::bind(&Publisher::marketDataReceive, &pub, std::placeholders::_1));

    // 订阅标的
    cad.subscribe(config.getInstrumentId());
}