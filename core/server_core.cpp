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

#include "server_core.h"

#include <iostream>
#include "spdlog/spdlog.h"

ServerCore::ServerCore()
{
    spdlog::info("ServerCore constructor");
};

ServerCore::~ServerCore()
{
    spdlog::info("ServerCore deconstructor");
};

void ServerCore::tick(){
    // spdlog::info("ServerCore tick");
};

void ServerCore::initialize()
{
    spdlog::info("ServerCore initialize");
}
