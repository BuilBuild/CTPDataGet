/*
 * @Author: LeiJiulong
 * @Date: 2025-02-20 07:41:42
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-20 07:42:51
 * @Description:
 */
#pragma once

#include <ctime>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdint>

namespace self_time_mk{

// 高效解析时间戳（毫秒级）
inline int64_t ConvertToTimestamp(const std::string &datetime)
{
    // 格式: "YYYYMMDD HH:mm:ss.fff"
    int year, month, day, hour, minute, second, millisecond;

    // 直接解析字符串（比流操作更快）
    // 使用 sscanf 直接解析字符串，比 istringstream 快 3-5 倍。
    if (sscanf(datetime.c_str(), "%4d%2d%2d %2d:%2d:%2d.%3d",
                &year, &month, &day,
                &hour, &minute, &second, &millisecond) != 7)
    {
        return -1; // 格式错误
    }

    // 初始化 tm 结构体
    struct tm tm;
    memset(&tm, 0, sizeof(tm)); // 清空结构体
    tm.tm_year = year - 1900;   // 年份从 1900 开始
    tm.tm_mon = month - 1;      // 月份从 0 开始
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;

    // 转换为秒级时间戳（本地时区）
    time_t timestamp = mktime(&tm);
    if (timestamp == -1)
    {
        return -1; // 非法时间
    }

    // 返回毫秒级时间戳
    return static_cast<int64_t>(timestamp) * 1000 + millisecond;
}


}
