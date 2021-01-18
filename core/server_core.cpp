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
