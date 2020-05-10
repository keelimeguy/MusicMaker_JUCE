#pragma once

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

class Logger {
public:
    static void Init();

    static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
};

// Logging macros
#define PRINT_TRACE(...)    ::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define PRINT_INFO(...)     ::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define PRINT_WARN(...)     ::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define PRINT_ERROR(...)    ::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define PRINT_CRITICAL(...) ::Logger::GetCoreLogger()->critical(__VA_ARGS__)
