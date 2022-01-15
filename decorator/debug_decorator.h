

#pragma once
#include "base_decorator.h"

class DebugDecorator : public BaseDecorator
{
public:
    static const uint16_t DECO_ID;
    DebugDecorator() : BaseDecorator(){
        this->initialize();
    };
    std::string to_string() override;
    void initialize() override;
};
