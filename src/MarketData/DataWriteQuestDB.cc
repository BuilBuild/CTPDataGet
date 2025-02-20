/*
 * @Author: LeiJiulong
 * @Date: 2025-02-20 10:20:14
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-20 11:14:38
 * @Description:
 */
#include "MarketData/DataWriteQuestDB.h"
#include <questdb/ingress/line_sender.hpp>

// #include ""

DataWriteQuestDB::DataWriteQuestDB(Config *config)
{
}

void DataWriteQuestDB::specificWrite(const OrderBook &)
{
    auto sender = questdb::ingress::line_sender::from_conf(
        // "http::addr=127.0.0.1:9000;username=Future;password=quest;");
        "http::addr=localhost:9000;username=admin;password=quest;");
    questdb::ingress::line_sender_buffer buffer;
    buffer
        .table("trades")
        .symbol("symbol", "ETH-USD")
        .symbol("side", "sell")
        .column("price", 2615.54)
        .column("amount", 0.00044)
        .at(questdb::ingress::timestamp_nanos::now());

    sender.flush(buffer);
    
}
