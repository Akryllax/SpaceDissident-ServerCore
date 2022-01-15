

#include <algorithm>
#include "spdlog/spdlog.h"
// #include <concepts>
#include "base_message.h"
#include "base_decorator.h"
#include "message_type_id.h"
#include "deco.h"

const uint16_t BaseMessage::MSG_TYPE_ID = MSG_TYPE_ID_BASE;

BaseMessage::BaseMessage()
{
    spdlog::trace("Creating new BaseMessage");
};

BaseMessage::~BaseMessage()
{
}

int BaseMessage::getDecoratorCount()
{
    return this->_decoList.size();
}

