#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class ConfigHolder
{
public:
    ConfigHolder();
    ~ConfigHolder();
    void add(const std::string &key, const std::string &value);
    std::string get(const std::string &key);
    size_t size();

private:
    std::unordered_map<std::string, std::string> config;
    std::vector<std::pair<std::string, std::string>> configLines;
};
