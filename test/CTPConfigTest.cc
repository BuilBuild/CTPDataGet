/*
 * @Author: LeiJiulong
 * @Date: 2025-02-18 22:10:18
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-19 07:29:55
 * @Description: 
 */
#include <iostream>
#include "MarketData/CTPConfig.h"


int main()
{
    CTPConfig c("/home/leijiulong/temp/ctp_data/config.ini");

    std::cout << "1" << std::endl;
    std::cout << c.path() << std::endl;
    std::cout << c.gTradeFrontAddr() << std::endl;
    
    return 0;
}