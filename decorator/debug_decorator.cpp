

#include "debug_decorator.h"
#include "deco_id.h"
#include "spdlog/spdlog.h"

const uint16_t DebugDecorator::DECO_ID = DECO_ID_DEBUG;

std::string DebugDecorator::to_string() const
{
  return "DebugDecorator";
};

void DebugDecorator::initialize()
{
  spdlog::trace("Creating new DebugDecorator");
}