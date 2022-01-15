

#pragma once
#include "config_reader.h"
#include <vector>
#include "server_core_module.h"
#include "config_holder.h"

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
