/*
 * @Author: LeiJiulong
 * @Date: 2025-03-02 09:50:08
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-02 10:57:54
 * @Description: 
 */
#include "Trader/MSGHUB/QuestDBSubscriberWriter.h"


#include <iostream>

int main()
{
    QuestDBSubscriberConfig config{};
    config.host = "127.0.0.1:9000";
    config.username = "admin";
    config.password = "quest";
    config.minPoolSize = 2;
    config.maxPoolSize = 10;
    QuestDBSubscriberWriter writer(config);
    for(int i = 0; i < 10; ++i)
    {
        OrderBook orderBook{};
        sprintf(orderBook.InstrumentID, "%s", "BTCUSDT");
        writer.orderBookWrite(orderBook);
    }
    return 0;
}