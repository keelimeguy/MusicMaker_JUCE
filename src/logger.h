#pragma once

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

class Logger {
public:
    static void Init();

    static auto &GetCoreLogger() { return core_logger_; }
private:
    static std::shared_ptr<spdlog::logger> core_logger_;

    Logger() {}
};

// Logging macros
#define PRINT_DEBUG(...)    ::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define PRINT_LOG(...)      ::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define PRINT_WARNING(...)  ::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define PRINT_ERROR(...)    ::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define PRINT_CRITICAL(...) ::Logger::GetCoreLogger()->critical(__VA_ARGS__)
