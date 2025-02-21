/*
 * @Author: LeiJiulong
 * @Date: 2025-02-20 03:14:21
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-21 14:17:15
 * @Description: 
 */
#pragma once

#include "BaseType.hpp"

class Writer
{
    public:
        virtual void toWrite(const OrderBook&) = 0;
};

class WriterAdaptee
{
public:
    virtual void specificWrite(const OrderBook&) = 0;
};

