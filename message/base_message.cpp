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

#include "base_message.h"
#include <algorithm>
#include "spdlog/spdlog.h"
#include "base_decorator.h"
#include <concepts>
#include "deco_id.h"

const uint16_t deco::BaseDecorator::DECO_ID = DECO_ID_BASE;

BaseMessage::BaseMessage(){
    spdlog::trace("Creating new BaseMessage");
};

BaseMessage::~BaseMessage()
{
    std::for_each(this->_decoList.begin(), this->_decoList.end(), [this](deco::BaseDecorator const &deco) {
        // this->removeDecorator(deco);
    });
}

template <>
bool BaseMessage::removeDecorator<deco::BaseDecorator>()
{
    spdlog::trace("BaseMessage::removeDecorator");
    auto item = std::find_if(this->_decoList.begin(), this->_decoList.end(), [](auto it) {
        return std::is_base_of<decltype(it), deco::BaseDecorator>();
    });

    bool result = false;
    if (item != this->_decoList.end())
    {
    }

    return result;
};
