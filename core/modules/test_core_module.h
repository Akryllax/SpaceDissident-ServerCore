#pragma once

#include "server_core_module.h"

class TestCoreModule : public ServerCoreModule
{
public:
  static const uint16_t CORE_MOD_ID;
  TestCoreModule() = default;
};