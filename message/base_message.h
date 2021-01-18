#pragma once
#include <vector>
#include "base_decorator.h"

class BaseMessage
{
public:
    BaseMessage();
    ~BaseMessage();

protected:
    std::vector<deco::BaseDecorator> _decoList;

public:
    static const uint16_t MSG_TYPE_ID;

public:
    template <typename T>
    const T &getDecorator();

    template <typename T>
    void addDecorator();

    template <typename T>
    bool removeDecorator();
};
