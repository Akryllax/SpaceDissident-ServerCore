#pragma once

#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h" // or "../stdout_sinks.h" if no colors needed
#include "spdlog/spdlog.h"

void spdlog_init()
{
  spdlog::trace("Running spdlog_init()");
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

  auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/server_log.log", true);
  // auto file_sink = spdlog::create_async<spdlog::sinks::basic_file_sink_mt>("async_file_logger", "core.log");

  // or you can even set multi_sink logger as default logger
  spdlog::set_default_logger(std::make_shared<spdlog::logger>(
      "multi_sink", spdlog::sinks_init_list({console_sink, file_sink})));
  auto logger = spdlog::get("multi_sink");
  logger->set_pattern("[core] [%^%l%$] %v");
  logger->set_level(spdlog::level::trace);
};

void spdlog_init(std::string filename)
{
  spdlog::trace("Running spdlog_init(filename)");
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

  auto file_sink =
      std::make_shared<spdlog::sinks::basic_file_sink_mt>(fmt::format("logs/{}", filename), true);

  // or you can even set multi_sink logger as default logger
  spdlog::set_default_logger(std::make_shared<spdlog::logger>(
      "multi_sink", spdlog::sinks_init_list({console_sink, file_sink})));
  auto logger = spdlog::get("multi_sink");
  logger->set_pattern("[core] [%^%l%$] %v");
  logger->set_level(spdlog::level::trace);
}
