#include "modules/test_core_module.h"

const uint16_t TestCoreModule::CORE_MOD_ID = CORE_MOD_TEST;

void onInitialize(const ServerContext& coreCtx)
{
  spdlog::trace("TestCoreModule::onInitialize()");
  // coreCtx.insert({"test", "initialized"});
}

void onConfig(const ServerContext& coreCtx)
{
  spdlog::trace("TestCoreModule::onConfig()");
}

void onTick(const ServerContext& coreCtx)
{
  spdlog::trace("TestCoreModule::onTick()");
}