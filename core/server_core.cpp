

#include "server_core.h"

#include <iostream>
#include "spdlog/spdlog.h"

ServerCore::ServerCore()
{
    spdlog::trace("ServerCore constructor");
};

ServerCore::~ServerCore()
{
    spdlog::trace("ServerCore deconstructor");
};

void ServerCore::tick(){
    // spdlog::trace("ServerCore tick");
};

void ServerCore::initialize()
{
    spdlog::trace("ServerCore initialize");
}
