/*
 * @Author: LeiJiulong
 * @Date: 2025-02-28 08:27:06
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-28 14:42:12
 * @Description: 
 */
#pragma once

#include "ICTPStrategy.h"

class MaCTPStrategy : public ICTPStrategy
{
public:
    MaCTPStrategy() = delete;
    explicit MaCTPStrategy(const ICTPStrategyConfig& config);
    ~MaCTPStrategy();

};