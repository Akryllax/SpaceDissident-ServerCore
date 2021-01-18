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

#pragma once
#include <type_traits>
#include "base_decorator.h"
#include "base_message.h"

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

namespace deco
{
    template <typename T>
    typename std::vector<T*>::iterator search_deco(std::vector<T*> &decoList)
    {
        auto item = decoList.begin();
        for (; item != decoList.end(); item++)
        {
            if (dynamic_cast<T *>(*item) != nullptr)
                break;
        }

        return item;
    }
}; // namespace deco