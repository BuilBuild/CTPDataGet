/*
 * @Author: LeiJiulong
 * @Date: 2025-02-18 21:34:51
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-20 01:50:01
 * @Description: 
 */
#pragma once

#include "Config.h"
#include "CTP/ThostFtdcMdApi.h"
#include "json.hpp"

#include <memory>

class CTPConfig : public Config
{
    using json = nlohmann::json;
public:
    CTPConfig(std::string path);
    const std::string& path();
    const std::vector<std::string>& getInstrumentId();
    const std::string& gTradeFrontAddr();
    CThostFtdcReqUserLoginField* loginReq(){return &loginReq_;};
    
private:
    void init();
private:
    std::string CTPConfigPath_;
    std::unique_ptr<json> configJson_;

    std::string gTradeFrontAddr_;
    CThostFtdcMdApi *pUserApi = nullptr;
    CThostFtdcReqUserLoginField loginReq_{};
    std::vector<std::string> instrumentId_;
};