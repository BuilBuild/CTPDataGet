/*
 * @Author: LeiJiulong
 * @Date: 2025-03-01 13:03:07
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-01 13:13:29
 * @Description: 
 */

 #include "Trader/Strategys/MaCTPStrategy.h"

 #include <iostream>
 #include <thread>
 #include <chrono>

int main(int argc, char *argv[])
{
    // 初始化配置
    ICTPStrategyConfig config{};
    config.subAddr_ = "tcp://localhost:5556";
    config.orderAddr_ = "tcp://localhost:5557";
    config.instruments_ = {"ag2504", "bu2504"};
    MaCTPStrategy strategy(config);
    snowid::Snowflake idGenerator(1, 1);
    while (true)
    {
      std::cout << "Waiting for order request..." << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      OrderRequest orderRequest{};
      orderRequest.orderId = idGenerator.Generate();
      orderRequest.symbol = "ag2504";
      orderRequest.side = OrderSide::Buy;
      orderRequest.quantity = 1;
      orderRequest.price = 4700;  
      strategy.addOrder(orderRequest);
    }
    
}
