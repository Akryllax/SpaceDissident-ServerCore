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

// GameServerCore0.cpp : Defines the entry point for the application.
//

#include "GameServerCore0.h"
#include "core/server_core.h"
#include <chrono>
#include <cstdint>
#include "spdlog/spdlog.h"
#include "basic_setup.h"
#include "base_message.h"

using namespace std;
using namespace chrono;

using frame = duration<int32_t, ratio<1, 60>>;
using ms = duration<float, milli>;

int main()
{
    basic_setup();

    spdlog::info("Main initialization...");
    ServerCore serverCore;
    serverCore.initialize();

    time_point<steady_clock> fpsTimer(steady_clock::now());
    frame FPS{};

    spdlog::info("Initialization finished");
    spdlog::info("Running main loop...");
    while (true)
    {
        FPS = duration_cast<frame>(steady_clock::now() - fpsTimer);
        if (FPS.count() >= 1)
        {
            fpsTimer = steady_clock::now();

            spdlog::trace("CPS: {}", FPS.count() * 60);
            serverCore.tick();
        }
    }
    return 0;
}
