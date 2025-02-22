/*
 * @Author: LeiJiulong
 * @Date: 2025-02-22 23:46:52
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-23 00:04:01
 * @Description: 
 */
#pragma once

#include "Executor.h"
#include "CTP/ThostFtdcTraderApi.h"

// CTP交易接口执行器
class CTPTraderApiExecutor : public Executor ,public CThostFtdcTraderSpi
{
public:
    CTPTraderApiExecutor() = delete;
    CTPTraderApiExecutor(const std::string &configPath);
    void execute(const OrderRequest& orderReq) override;
    virtual ~CTPTraderApiExecutor() = default;

private:
    void init();
    CThostFtdcTraderApi* traderApi_;
    // 用户登陆信息
    CThostFtdcReqUserLoginField pReqUserLoginField_;
};