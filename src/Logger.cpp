#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;

void Logger::Init() {
    try {

#ifdef DEBUG
        auto loglevel = spdlog::level::trace;
#else
        auto loglevel = spdlog::level::info;
#endif

        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("MusicMaker.log", true));

        logSinks[0]->set_pattern("%^[%T] %n: %v%$");
        logSinks[1]->set_pattern("[%T] [%l] %n: %v");

        s_CoreLogger = std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
        spdlog::register_logger(s_CoreLogger);
        s_CoreLogger->set_level(loglevel);
        s_CoreLogger->flush_on(loglevel);

    } catch (const spdlog::spdlog_ex &ex) {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
}
