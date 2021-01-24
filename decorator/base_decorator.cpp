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

#include "base_decorator.h"
#include "deco_id.h"
#include "spdlog/spdlog.h"

const uint16_t BaseDecorator::DECO_ID = DECO_ID_BASE;

BaseDecorator::BaseDecorator()
{
    this->initialize();
};


void BaseDecorator::initialize()
{
    spdlog::trace("Creating new BaseDecorator");
}

/**
 * BaseDecorator
 *  Use to implement actions into visitors. Only *real* way to implement functionality into the network stack.
 * @param  {BaseMessage} msg : Const reference to owning message object.
 */
void BaseDecorator::visit(const BaseMessage& msg)
{
    //Base decorator does nothing
}