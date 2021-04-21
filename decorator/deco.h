#ifndef DECO_H_
#define DECO_H_
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

#include <type_traits>
#include <vector>
// #include "base_decorator.h"
// #include "base_message.h"

class BaseMessage;
class BaseDecorator;

namespace DecoratorUtils
{
    template <class T>
    static void addDecorator(const BaseMessage &msg)
    {
        static_assert(std::is_base_of<BaseDecorator, T>::value, "T must inherit from BaseDecorator");
    };

    template <class T>
    static void removeDecorator(const BaseMessage &msg)
    {
        static_assert(std::is_base_of<BaseDecorator, T>::value, "T must inherit from BaseDecorator");
    };

    template <class T> //TODO This is aweful, please refactor
    static T *search_deco(std::vector<BaseDecorator *> &decoList)
    {
        auto item = decoList.begin();
        for (; item != decoList.end(); item++)
        {
            if (dynamic_cast<T *>(*item) != nullptr)
                break;
        }

        return (item != decoList.end()) ? (T *)(*item) : nullptr;
    };
}; // namespace deco
#endif