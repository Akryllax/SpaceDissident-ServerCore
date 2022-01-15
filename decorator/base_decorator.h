

#pragma once
#include <cinttypes>
#include <string>
#include "deco.h"
#include "base_message.h"

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
