#pragma once

#include <algorithm>
#include <type_traits>
#include <vector>

class BaseMessage;
class BaseDecorator;

namespace DecoratorUtils
{
template <class T>
static void addDecorator(const BaseMessage& msg)
{
  static_assert(std::is_base_of<BaseDecorator, T>::value, "T must inherit from BaseDecorator");
};

template <class T>
static void removeDecorator(const BaseMessage& msg)
{
  static_assert(std::is_base_of<BaseDecorator, T>::value, "T must inherit from BaseDecorator");
};

template <class T>
  static T* searchDecorator(std::vector<BaseDecorator*>& decoList)
  {
    static_assert(std::is_base_of<BaseDecorator, T>::value, "T must inherit from BaseDecorator");

    auto it = std::find_if(decoList.begin(), decoList.end(), [](BaseDecorator* deco) {
      return dynamic_cast<T*>(deco) != nullptr;
    });

    return (it != decoList.end()) ? dynamic_cast<T*>(*it) : nullptr;
  }

}; // namespace DecoratorUtils
