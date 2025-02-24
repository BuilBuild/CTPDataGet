/*
 * @Author: LeiJiulong
 * @Date: 2025-02-22 23:42:43
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-25 01:40:48
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

// 订单转换器接口
class OrderConverterFactory
{
public:
    OrderConverterFactory() = delete;
    OrderConverterFactory(const OrderConverterFactory&) = delete;
    OrderConverterFactory& operator=(const OrderConverterFactory&) = delete;
    explicit OrderConverterFactory(Executor* executor) : executor_(executor) {}
    // 订单转换
    virtual bool convert(const OrderRequest& orderReq) = 0;

    virtual ~OrderConverterFactory() = default;
private:
    Executor* executor_;
};
