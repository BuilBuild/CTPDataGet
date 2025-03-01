/*
 * @Author: LeiJiulong
 * @Date: 2025-03-01 14:09:08
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-01 14:10:53
 * @Description: 
 */
#pragma once

#include <chrono>


namespace SelfUtil 
{
// 获取当前时间戳
int64_t get_timestamp()
{

    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ).count();
}

}
