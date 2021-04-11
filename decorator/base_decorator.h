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
#include <cinttypes>
#include <string>
#include "deco.h"
#include "base_message.h"

class BaseMessage;

class BaseDecorator
{
public:
    BaseDecorator();
    virtual ~BaseDecorator(){};
    static const uint16_t DECO_ID;

public:
    virtual std::string to_string()
    {
        return "BaseDecorator";
    }

public:
    virtual void initialize();

public:
    virtual void visit(const BaseMessage& msg);
};
