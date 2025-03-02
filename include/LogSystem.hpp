/*
 * @Author: LeiJiulong
 * @Date: 2025-03-02 13:47:22
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-02 20:49:58
 * @Description: 
 */
#pragma once
#include "NonCopyAble.hpp"

#include <unordered_map>
#include <string>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <mutex>

// 日志系统
class LogSystem : public NonCopyAble
{
public:
    // 初始化日志系统
    static void InitLogSystem(const std::string &basePath = "./logs", size_t queueSize=8192, size_t threadCount=1)
    {
        static std::once_flag flag;
        std::call_once(flag, [&]() {
            spdlog::init_thread_pool(queueSize, threadCount);
            GetInstance().basePath_ = basePath;
        });
    }
    // 注册模块日志
    static std::shared_ptr<spdlog::logger> RegisterLogger(
        const std::string &moduleName, 
        spdlog::level::level_enum level = spdlog::level::info,
        size_t maxFileSize = 1024 * 1024 * 100, int maxFiles = 5)
    {
        std::lock_guard<std::mutex> lock(GetInstance().mtx_);
        if (auto it = GetInstance().loggers_.find(moduleName); it != GetInstance().loggers_.end())
        {
            return it->second;
        }

        try {
            auto sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                GetInstance().basePath_ + "/" + moduleName + ".log", maxFileSize, maxFiles);
            auto logger = std::make_shared<spdlog::async_logger>(moduleName, sink,
               spdlog::thread_pool(), spdlog::async_overflow_policy::block);
            
            logger->set_level(level);
            logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [thread:%t %s:%!:%# %l] %v");
            spdlog::register_logger(logger);
            GetInstance().loggers_.emplace(moduleName, logger);
            return logger;

        }
        catch (const spdlog::spdlog_ex &ex){
            throw std::runtime_error("LogSystem::RegisterLogger() failed: " + std::string(ex.what()));
        }

    }

    // 设置日志级别
    static void SetLogLevel(spdlog::level::level_enum level)
    {
        std::lock_guard<std::mutex> lock(GetInstance().mtx_);
        for(auto& [name, logger] : GetInstance().loggers_)
        {
            logger->set_level(level);
        }
    }


private:
    // 获取日志系统实例
    static LogSystem& GetInstance()
    {
        static LogSystem instance;
        return instance;
    }

private:
    std::string basePath_;  // 日志文件路径
    std::mutex mtx_;        // 日志系统锁
    std::unordered_map<std::string, std::shared_ptr<spdlog::async_logger>> loggers_;    // 日志模块
    
};

#define LOG_INFO(...) SPDLOG_LOGGER_INFO(this->logger_, __VA_ARGS__)
#define LOG_WARN(...) SPDLOG_LOGGER_WARN(this->logger_, __VA_ARGS__)
#define LOG_ERROR(...) SPDLOG_LOGGER_ERROR(this->logger_, __VA_ARGS__)
#define LOG_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(this->logger_, __VA_ARGS__)
#define LOG_DEBUG(...) SPDLOG_LOGGER_DEBUG(this->logger_, __VA_ARGS__)
#define LOG_TRACE(...) SPDLOG_LOGGER_TRACE(this->logger_, __VA_ARGS__)