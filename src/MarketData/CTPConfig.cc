/*
 * @Author: LeiJiulong
 * @Date: 2025-02-18 21:35:57
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-20 01:49:28
 * @Description: 
 */
#include "MarketData/CTPConfig.h"

#include <fstream>


CTPConfig::CTPConfig(std::string path):Config(path)
{
    CTPConfigPath_ = ini_->GetValue("CTP", "ConfigPath");

    std::ifstream f(CTPConfigPath_);
    if(f.is_open())
    {
        std::string json_s((std::istreambuf_iterator<char>(f)),
                std::istreambuf_iterator<char>());
        configJson_ = std::make_unique<json>(json::parse(json_s));
    }
    else
    {
        perror("CTPConfigPath_ file open error \n");
        exit(-1);
    }
    init();
}

void CTPConfig::init()
{
    using string = std::string;
    sprintf(loginReq_.BrokerID,"%s",string(configJson_->at("BrokerID")).c_str());
    sprintf(loginReq_.UserID,"%s", string(configJson_->at("UserID")).c_str());
    sprintf(loginReq_.Password,"%s", string(configJson_->at("PassWord")).c_str());
    gTradeFrontAddr_ = string(configJson_->at("gTradeFrontAddr")).c_str();
    
    auto ic = configJson_->at("InstrumentID");
    for(auto t: ic)
    {
        instrumentId_.emplace_back(t);
    }
}

const std::vector<std::string> &CTPConfig::getInstrumentId()
{
    return instrumentId_;
}

const std::string& CTPConfig::gTradeFrontAddr()
{
    return gTradeFrontAddr_;
}

const std::string &CTPConfig::path()
{
    // TODO: 在此处插入 return 语句
    return CTPConfigPath_;
}