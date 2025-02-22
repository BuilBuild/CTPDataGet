/*
 * @Author: LeiJiulong
 * @Date: 2025-02-22 23:52:16
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-23 00:29:19
 * @Description: 
 */
#include "Trader/EMS/CTPTraderApiExecutor.h"
#include "SimpleIni.h"
#include "json.hpp"

void CTPTraderApiExecutor::execute(const OrderRequest& orderReq)
{
    // 执行订单
}

CTPTraderApiExecutor::CTPTraderApiExecutor(const std::string &configPath)
{
    // 配置登陆信息
    CSimpleIniA ini;
    ini.LoadFile(configPath.c_str());
    const char* brokerID = ini.GetValue("CTP", "BrokerID", "");
    const char* userID = ini.GetValue("CTP", "UserID", "");
    const char* password = ini.GetValue("CTP", "Password", "");
    const char* frontAddr = ini.GetValue("CTP", "FrontAddr", "");
    sprintf(pReqUserLoginField_.BrokerID, "%s", brokerID);
    sprintf(pReqUserLoginField_.UserID, "%s", userID);
    sprintf(pReqUserLoginField_.Password, "%s", password);
    sprintf(frontAddr_, "%s", frontAddr);
    traderApi_ = CThostFtdcTraderApi::CreateFtdcTraderApi();

    init();
}
void CTPTraderApiExecutor::init()
{
    traderApi_->RegisterSpi(this);
    traderApi_->RegisterFront(frontAddr_);
    traderApi_->Init();
    static int requestId = 0;
    traderApi_->ReqUserLogin(&pReqUserLoginField_, requestId++);
}

CTPTraderApiExecutor::~CTPTraderApiExecutor()
{
    
}