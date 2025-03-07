/*
 * @Author: LeiJiulong
 * @Date: 2025-03-07 14:17:56
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-07 14:36:58
 * @Description: 
 */
#pragma once
#include <csignal>
#include <unistd.h>
#include <cstring>
#include "version.h" // 包含生成的版本头文件

 // 异步信号安全的输出函数
void safe_print(const char* msg) 
{
    write(STDERR_FILENO, msg, strlen(msg));
}

void signal_handler(int sig)
{
    safe_print("\n--- Crash Report ---\n");
    safe_print("Error occurred please notify developer\n");
    safe_print("Version     : "); safe_print(GIT_VERSION);  safe_print("\n");
    safe_print("Branch      : "); safe_print(GIT_BRANCH);  safe_print("\n");
    safe_print("Compiled    : "); safe_print(COMPILE_TIME); safe_print("\n");
    // safe_print("PID      : "); safe_print(std::to_string(getpid())); safe_print("\n");
    safe_print("GIT_COMMIT  : "); safe_print(GIT_COMMIT); safe_print("\n");
    safe_print("Signal      : "); safe_print(strsignal(sig)); safe_print("\n");
    safe_print("-------------------\n");

    // 恢复默认信号处理并重新触发崩溃（生成 core dump）
    signal(sig, SIG_DFL);
    raise(sig);
}

// 安装信号处理函数
#define INSTALL_CRASH_HANDLER() signal(SIGSEGV, signal_handler);signal(SIGABRT, signal_handler);