/*
 * @Author: LeiJiulong
 * @Date: 2025-02-22 23:52:16
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-22 23:56:47
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
    // 初始化
    
    init();
}