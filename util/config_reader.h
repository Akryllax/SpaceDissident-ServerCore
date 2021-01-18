#pragma once
#include <string>
#include <filesystem>

class ConfigReader
{
public:
    ConfigReader(std::filesystem::path path);
    ConfigReader(std::string path);

protected:
    std::filesystem::path _filepath;
};
