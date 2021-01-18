#pragma once
#include <type_traits>
#include "base_decorator.h"
#include "base_message.h"

namespace deco
{
    template <class T>
    void addDecorator(const BaseMessage &msg)
    {
        static_assert(std::is_base_of<BaseDecorator, T>::value, "T must inherit from BaseDecorator");
    }

    template <class T>
    void removeDecorator(const BaseMessage &msg)
    {
        static_assert(std::is_base_of<BaseDecorator, T>::value, "T must inherit from BaseDecorator");
    }
} // namespace deco
