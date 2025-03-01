/*
 * @Author: LeiJiulong
 * @Date: 2025-02-28 08:27:06
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-28 14:42:12
 * @Description: 
 */
#pragma once

#include "ICTPStrategy.h"

// 均线策略，使用均线交叉进行开仓和平仓操作
class MaCTPStrategy : public ICTPStrategy
{
public:
    MaCTPStrategy() = delete;
    explicit MaCTPStrategy(const ICTPStrategyConfig& config);
    ~MaCTPStrategy();

};