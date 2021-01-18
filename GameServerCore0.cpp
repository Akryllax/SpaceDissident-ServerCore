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


    BaseMessage msg;


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

            spdlog::info("CPS: {}", FPS.count() * 60);
            serverCore.tick();
        }
    }
    return 0;
}
