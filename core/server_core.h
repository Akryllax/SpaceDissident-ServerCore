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
#include "../util/config_reader.h"
#include <vector>
#include "server_core_module.h"
#include "../util/config_holder.h"

class ServerCore
{
private:
    std::vector<ServerCoreModule *> coreModules;

public:
    ServerCore();
    ~ServerCore();

    void tick();
    void initialize();

    template <typename ServerCoreModule>
    int addCoreModule()
    {
        return -1;
    }

protected:
    ConfigHolder *config;
};
