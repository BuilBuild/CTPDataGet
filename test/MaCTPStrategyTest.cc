/*
 * @Author: LeiJiulong
 * @Date: 2025-02-28 14:47:36
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-01 09:45:41
 * @Description: 
 */

 #include "Trader/Strategys/MaCTPStrategy.h"

 #include <iostream>
 #include <thread>
 #include <chrono>

 int main()
 {
    ICTPStrategyConfig config{};
    config.subAddr_ = "tcp://localhost:5556";
    config.orderAddr_ = "tcp://localhost:5557";
    config.instruments_ = {"ag2504", "bu2504"};
    MaCTPStrategy strategy(config);
    while (true)
    {
      std::cout << "Waiting for order request..." << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      OrderRequest orderRequest{};
      orderRequest.orderId = 12345;
      orderRequest.symbol = "ag2504";
      orderRequest.side = OrderSide::Buy;
      orderRequest.quantity = 1;
      orderRequest.price = 4700;  
      strategy.addOrder(orderRequest);
    }
    
 }
