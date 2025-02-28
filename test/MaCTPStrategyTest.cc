/*
 * @Author: LeiJiulong
 * @Date: 2025-02-28 14:47:36
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-28 14:47:38
 * @Description: 
 */

 #include "Trader/Strategys/MaCTPStrategy.h"

 #include <iostream>

 int main()
 {
    ICTPStrategyConfig config{};
    config.subAddr_ = "tcp://localhost:5556";
    config.instruments_ = {"ag2504", "bu2504"};
    MaCTPStrategy strategy(config);
 }
