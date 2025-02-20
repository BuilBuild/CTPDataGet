/*
 * @Author: LeiJiulong
 * @Date: 2025-02-18 22:10:18
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-20 12:42:50
 * @Description: 
 */
#include <iostream>
#include "MarketData/CTPConfig.h"


int main(int argc, char* argv[])
{
    
    CTPConfig c("/home/leijiulong/temp/CTPDataGet/config.ini");
    
    auto iniPtr = c.getIniPtr();
    const char* csvPath = iniPtr->GetValue("CSV", "CSVOutPutPath");
    std::cout << "csv path: " << csvPath << std::endl;
    std::cout << "1" << std::endl;
    std::cout << c.path() << std::endl;
    std::cout << c.gTradeFrontAddr() << std::endl;

    std::cout << argc << std::endl;
    if(argc >1)
    {
        std::cout << argv[1] << std::endl;
    }
    
    return 0;
}