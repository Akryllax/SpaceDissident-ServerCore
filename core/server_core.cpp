

#include "server_core.h"

#include "spdlog/spdlog.h"
#include <iostream>

ServerCore::ServerCore()
{
  spdlog::trace("ServerCore constructor");
};

ServerCore::~ServerCore()
{
  spdlog::trace("ServerCore deconstructor");
};

void ServerCore::tick()
{
  spdlog::trace("ServerCore tick");
  this->tickCoreModules();
};

void ServerCore::initialize()
{
  spdlog::trace("ServerCore initialize");
}

void ServerCore::tickCoreModules()
{
  spdlog::trace("ServerCore tickCoreModules");
  auto coreModules = this->getCoreModules();
  for(auto it = coreModules.begin(); it != coreModules.end(); it++)
  {
    (*it)->tick(this->_ctx);
  }
}