#ifndef DECO_H_
#define DECO_H_

#include <type_traits>
#include <vector>
// #include "base_decorator.h"
// #include "base_message.h"

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

template <class T> //TODO This is aweful, please refactor
static T* search_deco(std::vector<BaseDecorator*>& decoList)
{
  auto item = decoList.begin();
  for(; item != decoList.end(); item++)
  {
    if(dynamic_cast<T*>(*item) != nullptr)
      break;
  }

  return (item != decoList.end()) ? (T*)(*item) : nullptr;
};
}; // namespace DecoratorUtils
#endif