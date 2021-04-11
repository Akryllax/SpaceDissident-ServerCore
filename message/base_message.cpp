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

template <>
bool BaseMessage::removeDecorator<BaseDecorator>()
{
    spdlog::trace("BaseMessage::removeDecorator");

    auto item = deco::search_deco<BaseDecorator>(this->_decoList);
    bool result = false;
    if (item)
    {
        //TODO This is aweful
        // this->_decoList.erase(item);
        result = true;
    }

    return result;
};

int BaseMessage::getDecoratorCount()
{
    return this->_decoList.size();
}