#pragma once

#include "ServerCoreModule.h"

class TestCoreModule : public ServerCoreModule
{
public:
  static const uint16_t CORE_MOD_ID;
  TestCoreModule() = default;
};