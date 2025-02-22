/*
 * @Author: LeiJiulong
 * @Date: 2025-02-22 23:42:43
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-23 00:13:06
 * @Description: 
 */
#pragma once
#include "Trader/TraderBaseType.hpp"

#include <string>


// 执行器接口
class Executor
{
public:
    Executor() = default;
    // 执行订单
    virtual void execute(const OrderRequest& orderReq) = 0;

    virtual ~Executor() = default;
};
