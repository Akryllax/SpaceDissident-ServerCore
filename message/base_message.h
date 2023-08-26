#pragma once

#include <vector>
// #include <memory>
#include "base_decorator.h"
#include "decoUtils.h"
#include "spdlog/spdlog.h"

class BaseDecorator;

class BaseMessage
{
public:
  BaseMessage();
  ~BaseMessage();

protected:
  std::vector<BaseDecorator*> _decoList;

public:
  static const uint16_t MSG_TYPE_ID;

public:
  template <typename T>
  BaseDecorator* getDecorator()
  {
    spdlog::trace("BaseMessage::getDecorator");
    spdlog::trace("BaseMessage->_decoList size: {}", this->_decoList.size());

    return DecoratorUtils::searchDecorator<T>(this->_decoList);
  }

  template <typename T>
  bool addDecorator()
  {
    spdlog::trace("BaseMessage::addDecorator");

    auto item = DecoratorUtils::searchDecorator<T>(this->_decoList);
    bool result = false;

    spdlog::trace("BaseMessage::addDecorator isDecoratorPresent: {}", item != nullptr);

    if(!item)
    {
      spdlog::trace("BaseMessage::addDecorator adding new Decorator");
      auto deco = new T();
      this->_decoList.push_back(deco);
      result = true;
    }

    return result;
  }

  template <typename T>
  bool removeDecorator()
  {
    spdlog::trace("BaseMessage::removeDecorator");

    auto item = DecoratorUtils::searchDecorator<T>(this->_decoList);
    bool result = false;
    if(item)
    {
      //TODO This is aweful
      // this->_decoList.erase(item);
      result = true;
    }

    return result;
  };

  int getDecoratorCount();
};
