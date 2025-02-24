/*
 * @Author: LeiJiulong
 * @Date: 2025-02-22 23:52:16
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-25 01:20:41
 * @Description: 
 */
#include "Trader/EMS/CTPTraderApiExecutor.h"
#include "SimpleIni.h"
#include "json.hpp"

#include <iostream>
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

    strcpy(qryTradingAccountField_.BrokerID, pReqUserLoginField_.BrokerID);
    strcpy(qryTradingAccountField_.InvestorID, pReqUserLoginField_.UserID);

    init();
}
void CTPTraderApiExecutor::init()
{
    traderApi_->RegisterSpi(this);
    traderApi_->RegisterFront(frontAddr_);
    // traderApi_->SubscribePublicTopic(THOST_TERT_RESUME);
    // traderApi_->SubscribePrivateTopic(THOST_TERT_RESUME);
    // 开始连接
    traderApi_->Init();
}

void CTPTraderApiExecutor::OnFrontConnected()
{
    spdlog::info("CTPTraderApiExecutor::OnFrontConnected");
    traderApi_->ReqUserLogin(&pReqUserLoginField_, requestID_++);
}

void CTPTraderApiExecutor::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    char msg[1024]{};
    sprintf(msg, "CTPTraderApiExecutor::OnRspUserLogin: TradingDay=%s, LoginTime=%s, MaxOrderRef=%s, SHFETime=%s, DCETime=%s, CZCETime=%s, FFEXTime=%s, INETime=%s, ErrorID=%d, ErrorMsg=%s\n",
            pRspUserLogin->TradingDay, pRspUserLogin->LoginTime, pRspUserLogin->MaxOrderRef, pRspUserLogin->SHFETime, pRspUserLogin->DCETime, pRspUserLogin->CZCETime, pRspUserLogin->FFEXTime, pRspUserLogin->INETime, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
    
    spdlog::info(msg);
    bzero(msg, sizeof(msg));
    sprintf(msg, "CTPTraderApiExecutor::OnRspUserLogin: RequestID=%d, IsLast=%d", nRequestID, bIsLast);
    spdlog::info(msg);
    
    // 保存会话参数
    tradeFrontID_ = pRspUserLogin->FrontID;
    sessionID_ = pRspUserLogin->SessionID;
    bzero(orderRef_, sizeof(orderRef_));
    strcpy(orderRef_, pRspUserLogin->MaxOrderRef);

    // 投资者结算结果确认
    reqSettlementInfoConfirm();
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

void CTPTraderApiExecutor::reqSettlementInfoConfirm()
{
    CThostFtdcSettlementInfoConfirmField settlementConfirmReq{};
    strcpy(settlementConfirmReq.BrokerID, pReqUserLoginField_.BrokerID);
	strcpy(settlementConfirmReq.InvestorID, pReqUserLoginField_.UserID);
	int rt =traderApi_->ReqSettlementInfoConfirm(&settlementConfirmReq, requestID_++);
    if (!rt)
		spdlog::info(">>>>>>发送投资者结算结果确认请求成功");
    else
		spdlog::info("--->>>发送投资者结算结果确认请求失败");
}

void CTPTraderApiExecutor::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    char msg[1024]{};
    sprintf(msg, "CTPTraderApiExecutor::OnRspSettlementInfoConfirm: RequestID=%d, IsLast=%d", nRequestID, bIsLast);
    spdlog::info(msg);
    bzero(msg, sizeof(msg));
    sprintf(msg, "CTPTraderApiExecutor::OnRspSettlementInfoConfirm: BrokerID=%s, InvestorID=%s, ConfirmDate=%s, ConfirmTime=%s",
            pSettlementInfoConfirm->BrokerID, pSettlementInfoConfirm->InvestorID, pSettlementInfoConfirm->ConfirmDate, pSettlementInfoConfirm->ConfirmTime);
    spdlog::info(msg);
}

void CTPTraderApiExecutor::reqQueryTradingAccount()
{
    spdlog::info("CTPTraderApiExecutor::reqQueryTradingAccount");
    std::this_thread::sleep_for(std::chrono::milliseconds(700)); // 延迟查询
    auto rs = traderApi_->ReqQryTradingAccount(&qryTradingAccountField_,requestID_++);
    if (!rs)
        spdlog::info(">>>>>>发送查询资金账户请求成功");
    else
        spdlog::info(">>>>>>发送查询资金账户请求失败");
}

void CTPTraderApiExecutor::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    char msg[2048]{};
  
    spdlog::info(msg);
    std::cout << "资金账户查询成功" << std::endl;
    std::cout << "经纪公司代码:" << pTradingAccount->BrokerID << std::endl;
    std::cout << "投资者帐号:" << pTradingAccount->AccountID << std::endl;
    std::cout << "上次结算准备金:" << pTradingAccount->PreBalance << std::endl;
    std::cout << "入金金额:" << pTradingAccount->Deposit << std::endl;
    std::cout << "出金金额:" << pTradingAccount->Withdraw << std::endl;
    std::cout << "冻结的保证金:" << pTradingAccount->FrozenMargin << std::endl;
    std::cout << "冻结手续费:" << pTradingAccount->FrozenCommission << std::endl;
    bzero(msg, sizeof(msg));
    sprintf(msg, "CTPTraderApiExecutor::OnRspQryTradingAccount: RequestID=%d, IsLast=%d", nRequestID, bIsLast);
    spdlog::info(msg);
}



CTPTraderApiExecutor::~CTPTraderApiExecutor()
{
    traderApi_->Join();
}