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
#include <vector>
#include "base_decorator.h"

class BaseMessage
{
public:
    BaseMessage();
    ~BaseMessage();

protected:
    std::vector<deco::BaseDecorator> _decoList;

public:
    static const uint16_t MSG_TYPE_ID;

public:
    template <typename T>
    const T &getDecorator();

    template <typename T>
    void addDecorator();

    template <typename T>
    bool removeDecorator();
};
