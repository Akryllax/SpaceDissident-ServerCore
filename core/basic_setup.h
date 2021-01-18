#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h" // or "../stdout_sinks.h" if no colors needed
#include "spdlog/sinks/basic_file_sink.h"

void basic_setup()
{
    spdlog::info("Running basic_setup()");
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);
    console_sink->set_pattern("[core] [%^%l%$] %v");

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/server_log.log", true);
    // auto file_sink = spdlog::create_async<spdlog::sinks::basic_file_sink_mt>("async_file_logger", "core.log");
    file_sink->set_pattern("[core] [%^%l%$] %v");
    file_sink->set_level(spdlog::level::trace);

    // or you can even set multi_sink logger as default logger
    spdlog::set_default_logger(std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list({console_sink, file_sink})));
};
