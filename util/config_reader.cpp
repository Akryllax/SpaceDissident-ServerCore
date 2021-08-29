#include "config_reader.h"
#include <iostream>

ConfigReader::ConfigReader(std::filesystem::path path){

};

ConfigReader::ConfigReader(std::string path)
{
    if (std::filesystem::exists(path))
    {
        this->_configPath = std::filesystem::path(path);
    }
    else
    {
        spdlog::error("Config file not found: " + path);
    }
};
