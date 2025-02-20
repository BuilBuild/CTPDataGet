/*
 * @Author: LeiJiulong
 * @Date: 2025-02-18 21:21:19
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-18 22:31:25
 * @Description: 
 */
#include "MarketData/Config.h"
// #include "SimpleIni.h"


#include <string>

Config::Config(std::string path):configPath(path)
{
    ini_ = std::make_unique<CSimpleIniA>(
        /*bIsUtf8=*/true, 
        /*bMultiKey=*/true, 
        /*bMultiLine=*/true
    );
    ini_->LoadFile(configPath.c_str());
}