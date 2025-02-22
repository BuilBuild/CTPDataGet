/*
 * @Author: LeiJiulong
 * @Date: 2025-02-22 23:52:16
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-23 01:21:31
 * @Description: 
 */
#include "Trader/EMS/CTPTraderApiExecutor.h"
#include "SimpleIni.h"
#include "json.hpp"
#include <spdlog/spdlog.h>
#include <thread>

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
    traderApi_ ->SubscribePublicTopic(THOST_TERT_RESUME);
    traderApi_->Init();
    static int requestId = 0;
    traderApi_->ReqUserLogin(&pReqUserLoginField_, requestId++);
}

void CTPTraderApiExecutor::OnFrontConnected()
{
    spdlog::info("CTPTraderApiExecutor::OnFrontConnected");
    static int requestId = 0;
    traderApi_->ReqUserLogin(&pReqUserLoginField_, requestId++);
}

void CTPTraderApiExecutor::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    char msg[1024]{};
    sprintf(msg, "CTPTraderApiExecutor::OnRspUserLogin: TradingDay=%s, LoginTime=%s, MaxOrderRef=%s, SHFETime=%s, DCETime=%s, CZCETime=%s, FFEXTime=%s, INETime=%s, ErrorID=%d, ErrorMsg=%s",
            pRspUserLogin->TradingDay, pRspUserLogin->LoginTime, pRspUserLogin->MaxOrderRef, pRspUserLogin->SHFETime, pRspUserLogin->DCETime, pRspUserLogin->CZCETime, pRspUserLogin->FFEXTime, pRspUserLogin->INETime, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
    
    spdlog::info(msg);
    bzero(msg, sizeof(msg));
    sprintf(msg, "CTPTraderApiExecutor::OnRspUserLogin: RequestID=%d, IsLast=%d", nRequestID, bIsLast);
    spdlog::info(msg);
    // 查询资金账户
    static int requestId = 0;
    CThostFtdcQryTradingAccountField qryTradingAccountField{};
    sprintf(qryTradingAccountField.BrokerID, "%s", pReqUserLoginField_.BrokerID);
    strcpy(qryTradingAccountField.InvestorID, pReqUserLoginField_.UserID);
    std::this_thread::sleep_for(std::chrono::milliseconds(700)); // 有时候需要停顿一会才能查询成功
    traderApi_->ReqQryTradingAccount(&qryTradingAccountField, requestId++);
}

void CTPTraderApiExecutor::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    char msg[1024]{};
    sprintf(msg, "CTPTraderApiExecutor::OnRspQryTradingAccount: AccountID=%s, PreBalance=%lf, WithdrawQuota=%lf, WithdrawQuota=%lf, Credit=%lf, \
        Margin=%lf, Commission=%lf, CloseProfit=%lf, PositionProfit=%lf, ErrorID=%d, ErrorMsg=%s",
            pTradingAccount->AccountID, pTradingAccount->PreBalance, pTradingAccount->WithdrawQuota, 
            pTradingAccount->WithdrawQuota, pTradingAccount->Credit, pTradingAccount->PreMargin, 
            pTradingAccount->Commission, pTradingAccount->CloseProfit, pTradingAccount->PositionProfit, 
            pRspInfo->ErrorID, pRspInfo->ErrorMsg);
    spdlog::info(msg);
    bzero(msg, sizeof(msg));
    sprintf(msg, "CTPTraderApiExecutor::OnRspQryTradingAccount: RequestID=%d, IsLast=%d", nRequestID, bIsLast);
    spdlog::info(msg);
}

void CTPTraderApiExecutor::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    char msg[1024]{};
    sprintf(msg, "CTPTraderApiExecutor::OnRspError: ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
    spdlog::error(msg);
    bzero(msg, sizeof(msg));
    sprintf(msg, "CTPTraderApiExecutor::OnRspError: RequestID=%d, IsLast=%d", nRequestID, bIsLast);
    spdlog::error(msg);
}













CTPTraderApiExecutor::~CTPTraderApiExecutor()
{
    traderApi_->Join();
}