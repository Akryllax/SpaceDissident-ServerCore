#pragma once

#include "modules/core_mod_id.h"
#include "server_core_ctx.h"
#include "spdlog/spdlog.h"

class ServerCore;

class ServerCoreModule
{
public:
  virtual ~ServerCoreModule() = default;

public:
  static const uint16_t CORE_MOD_ID;

  void initialize(const ServerContext& coreCtx)
  {
    spdlog::trace("ServerCoreModule::initialize()");
    this->onInitialize(coreCtx);
  }
  void config(const ServerContext& coreCtx)
  {
    spdlog::trace("ServerCoreModule::config()");
    this->onConfig(coreCtx);
  }
  void tick(const ServerContext& coreCtx)
  {
    spdlog::trace("ServerCoreModule::tick()");
    this->onTick(coreCtx);
  }

  virtual void onInitialize(const ServerContext& coreCtx){};
  virtual void onConfig(const ServerContext& coreCtx){};
  virtual void onTick(const ServerContext& coreCtx){};
};
