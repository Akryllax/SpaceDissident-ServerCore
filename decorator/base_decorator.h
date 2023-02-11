

#pragma once
#include "base_message.h"
#include "deco.h"
#include <cinttypes>
#include <string>

class BaseMessage;

class BaseDecorator
{
public:
  BaseDecorator();
  virtual ~BaseDecorator(){};
  static const uint16_t DECO_ID;

public:
  virtual std::string to_string()
  {
    return "BaseDecorator";
  }

public:
  virtual void initialize();

public:
  virtual void visit(const BaseMessage& msg);
};
