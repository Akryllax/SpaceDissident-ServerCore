/*
 *   Copyright (c) 2021 Akryllax (akryllax@gmail.com)

 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.

 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <algorithm>
#include "spdlog/spdlog.h"
#include <concepts>
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
    // std::for_each(this->_decoList.begin(), this->_decoList.end(), [this](BaseDecorator const &deco) {
    //     // this->removeDecorator(deco);
    // });
}

template <>
bool BaseMessage::removeDecorator<BaseDecorator>()
{
    spdlog::trace("BaseMessage::removeDecorator");
    // auto item = std::find_if(this->_decoList.begin(), this->_decoList.end(), [](auto *it) {
    //     return std::is_base_of<decltype(it), BaseDecorator>();
    // });

    auto item = deco::search_deco<BaseDecorator>(this->_decoList);
    bool result = false;
    if (item != this->_decoList.end())
    {
        //TODO This is aweful
        this->_decoList.erase(item);
        result = true;
    }

    return result;
};

template <>
bool BaseMessage::addDecorator<BaseDecorator>()
{
    spdlog::trace("BaseMessage::addDecorator");
    // auto item = std::find_if(this->_decoList.begin(), this->_decoList.end(), [&](auto *it) {
    //     spdlog::trace("Searching for BaseDecorator: {}", it->to_string());
    //     return (static_cast<BaseDecorator*>(*it) != nullptr);
    // });


    auto item = deco::search_deco<BaseDecorator>(this->_decoList);
    bool result = false;

    spdlog::trace("BaseMessage::addDecorator isDecoratorPresent: {}", item != this->_decoList.end());

    if (item == this->_decoList.end())
    {
        spdlog::trace("BaseMessage::addDecorator adding new Decorator");
        auto deco = new BaseDecorator();
        this->_decoList.push_back(deco);
        result = true;
    }

    return result;
};

template <>
BaseDecorator *BaseMessage::getDecorator<BaseDecorator>()
{
    spdlog::trace("BaseMessage::getDecorator");
    spdlog::trace("BaseMessage->_decoList size: {}", this->_decoList.size());

    return *(deco::search_deco<BaseDecorator>(this->_decoList));
};

int BaseMessage::getDecoratorCount()
{
    return this->_decoList.size();
}