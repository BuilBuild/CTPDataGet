/*
 * @Author: LeiJiulong
 * @Date: 2025-03-07 14:20:12
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-07 14:20:15
 * @Description: 
 */
#include "GitBackTrace.hpp"

int main(int argc, char const *argv[])
{
    INSTALL_CRASH_HANDLER();
    int *p = nullptr;
    *p = 0;
    
    return 0;
}