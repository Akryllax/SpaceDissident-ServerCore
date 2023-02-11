#pragma once

#include "config_holder.h"
#include "config_reader.h"
#include "server_core_ctx.h"
#include "server_core_module.h"
#include <vector>

class ServerCore
{
private:
  ServerContext _ctx;
  std::vector<ServerCoreModule*> coreModules;

public:
  ServerCore();
  ~ServerCore();

  void tick();
  void initialize();

  //!TODO rework this, better initalization in the future
  template <typename tCoreModule>
  int addCoreModule(const tCoreModule& coreModule)
  {
    this->coreModules.push_back(coreModule);
    coreModule.initialize(this->_ctx);
    coreModule.config(this->_ctx);
    return true;
  }

  const std::vector<ServerCoreModule*>& getCoreModules()
  {
    return this->coreModules;
  }

protected:
  ConfigHolder* config;

  void tickCoreModules();
};
