

#pragma once
#include "base_message.h"
#include "decoUtils.h"
#include <cinttypes>
#include <string>

class BaseMessage;

class BaseDecorator
{
public:
  BaseDecorator();
  virtual ~BaseDecorator(){};
  static const uint16_t DECO_ID;
  virtual inline std::string to_string() const
  {
    return "BaseDecorator";
  }
  virtual void initialize();
  virtual void visit(const BaseMessage& msg);
};
