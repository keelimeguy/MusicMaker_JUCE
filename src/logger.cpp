#include "logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

std::shared_ptr<spdlog::logger> Logger::core_logger_;

void Logger::Init() {
    try {

#ifdef DEBUG
        auto log_level = spdlog::level::trace;
#else
        auto log_level = spdlog::level::info;
#endif

        std::vector<spdlog::sink_ptr> log_sinks;
        log_sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        log_sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("MusicMaker.log", true));

        log_sinks[0]->set_pattern("%^[%T] [%l] %n: %v%$");
        log_sinks[1]->set_pattern("[%T] [%l] %n: %v");

        core_logger_ = std::make_shared<spdlog::logger>("APP", begin(log_sinks), end(log_sinks));
        spdlog::register_logger(core_logger_);
        core_logger_->set_level(log_level);
        core_logger_->flush_on(log_level);

    } catch (const spdlog::spdlog_ex &ex) {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
}
