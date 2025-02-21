/*
 * @Author: LeiJiulong
 * @Date: 2025-02-18 20:35:28
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-21 14:40:29
 * @Description: 
 */

#include "MarketData/CTPMarketData.h"
#include <iostream>
#include <spdlog/spdlog.h>
#include <chrono>
#include <vector>


CTPMarketDataAdapter::CTPMarketDataAdapter()
{
    // writeCallBackThread_ = std::thread([this]{
    //     while(true)
    //     {
    //         std::function<void(void)> t;
    //         cbExcQueue_.pop(t);
    //         t();
    //     }
    // });
}

CTPMarketDataAdapter::~CTPMarketDataAdapter()
{
    pUserApi_->Join();
}

void CTPMarketDataAdapter::connect(Config *config)
{
    configPtr_ = dynamic_cast<CTPConfig*>(config);
    if (configPtr_ == nullptr) { // 必须检查是否转换成功
        spdlog::error("config error!");
        
    }
    else
    {
        init();
    }
}

void CTPMarketDataAdapter::subscribe(const std::vector<std::string> &symbols)
{
    std::unique_lock<std::mutex> lock(connectMtx_);
    spdlog::info("wait connect and login.......");
    // 等待连接
    auto status = cv.wait_for(lock, std::chrono::seconds(5), [this] {
        return loginFlag;  // 检查条件
    });

    if(status)
    {
        
        char** ppInstrumentID = new char*[symbols.size()];
        for(int i= 0;i< symbols.size(); ++i)
        {
            ppInstrumentID[i] = new char[symbols[i].size()+1];
            bzero(ppInstrumentID[i], symbols[i].size()+1);
            memcpy(ppInstrumentID[i],symbols[i].c_str(), symbols[i].size());
        }
        // 订阅行情
        pUserApi_->SubscribeMarketData(ppInstrumentID, symbols.size());

    }
    else
    {
        spdlog::critical("connect and login failed.......");
        exit(-1);
    } 
}


void CTPMarketDataAdapter::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    char info[256]{};
    sprintf(info, "Sub success! Instrument: %s, info: %s", pSpecificInstrument->InstrumentID, pRspInfo->ErrorMsg);
    spdlog::info(info);
}

void CTPMarketDataAdapter::init()
{
    // 开始初始化
    pUserApi_ =  CThostFtdcMdApi::CreateFtdcMdApi();
    pUserApi_->RegisterSpi(this);
    char frontAddr[128]{};
    sprintf(frontAddr, "%s", configPtr_->gTradeFrontAddr().c_str());
    pUserApi_->RegisterFront(frontAddr);
    pUserApi_->Init();
}

void CTPMarketDataAdapter::set_callback(MarketDataCallback cb)
{
    cbSetList_.emplace_back(cb);
    cb_ = cb;
}

void CTPMarketDataAdapter::disconnect()
{
}

void CTPMarketDataAdapter::OnFrontConnected()
{
    spdlog::info("onFront connected"); 
    // 开始登陆
    static int nRequestID = 0;
    pUserApi_->ReqUserLogin(configPtr_->loginReq(), nRequestID++);
}

void CTPMarketDataAdapter::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    spdlog::info("login success");
    // deng
    loginFlag = true;
    cv.notify_one();
}

void CTPMarketDataAdapter::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    // 设置将行情信息传回调
    for(auto c : cbSetList_)
    {
        c(*pDepthMarketData);
    }
}

void CTPMarketDataAdapter::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    char errorInfo[128]{};
    sprintf(errorInfo, "nRequestID: %d , bIsLast: %d , info: \'%s\'", nRequestID, bIsLast, pRspInfo->ErrorMsg);
    spdlog::warn(errorInfo);
};