#pragma once

#include "ServerCoreModule.h"
#include "config_holder.h"
#include "config_reader.h"
#include "server_core_ctx.h"
#include <memory>
#include <vector>

using CoreModulesPtrVector = std::vector<std::unique_ptr<ServerCoreModule>>;

class ServerCore
{
public:
  enum class MODULE_STATUS
  {
    NONE = 0,
    SUCCESS = 1,
    ERROR = 2
  };

public:
  ServerCore()
      : _ctx(/* initialize context */)
      , _config(std::make_unique<ConfigHolder>())
  {
    spdlog::trace("ServerCore constructor");
    initialize();
  }

  template <typename T>
  MODULE_STATUS addCoreModule(std::unique_ptr<T> coreModule)
  {
    if(!coreModule)
    {
      spdlog::error("Failed to add core module: nullptr received");
      return MODULE_STATUS::ERROR;
    }

    coreModule->initialize(_ctx);
    coreModule->config(_ctx);
    _coreModules.push_back(std::move(coreModule));
    return MODULE_STATUS::SUCCESS;
  }

  void tick() const
  {
    spdlog::trace("ServerCore::tick()");
  }

  void initialize()
  {
    spdlog::trace("ServerCore initialize");
  }

  const CoreModulesPtrVector& getCoreModules() const
  {
    return _coreModules;
  }

  void tickCoreModules()
  {
    spdlog::trace("ServerCore tickCoreModules");
    const auto& coreModules = this->getCoreModules();
    for(const auto& module : coreModules)
    {
      module->tick(_ctx);
    }
  }

private:
  ServerContext _ctx;
  CoreModulesPtrVector _coreModules;
  std::unique_ptr<ConfigHolder> _config;
};
