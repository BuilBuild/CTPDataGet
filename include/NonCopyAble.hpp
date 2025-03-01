/*
 * @Author: LeiJiulong
 * @Date: 2025-02-25 08:45:05
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-01 11:24:30
 * @Description: 
 */
#pragma once

// 禁止拷贝构造和赋值构造
class NonCopyAble
{
public:
    NonCopyAble() = default;
    NonCopyAble(const NonCopyAble&) = delete;
    NonCopyAble& operator=(const NonCopyAble&) = delete;
    virtual ~NonCopyAble() = default;
};
