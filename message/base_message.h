#pragma once
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

#include <vector>
// #include <memory>
#include "deco.h"
#include "base_decorator.h"
#include "spdlog/spdlog.h"

class BaseDecorator;

class BaseMessage
{

public:
    BaseMessage();
    ~BaseMessage();

protected:
    std::vector<BaseDecorator *> _decoList;

public:
    static const uint16_t MSG_TYPE_ID;

public:
    template <typename T>
    BaseDecorator *getDecorator()
    {
        spdlog::trace("BaseMessage::getDecorator");
        spdlog::trace("BaseMessage->_decoList size: {}", this->_decoList.size());

        return DecoratorUtils::search_deco<T>(this->_decoList);
    }

    template <typename T>
    bool addDecorator()
    {
        spdlog::trace("BaseMessage::addDecorator");

        auto item = DecoratorUtils::search_deco<T>(this->_decoList);
        bool result = false;

        spdlog::trace("BaseMessage::addDecorator isDecoratorPresent: {}", item != nullptr);

        if (!item)
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

        auto item = DecoratorUtils::search_deco<T>(this->_decoList);
        bool result = false;
        if (item)
        {
            //TODO This is aweful
            // this->_decoList.erase(item);
            result = true;
        }

        return result;
    };

    int getDecoratorCount();
};
