#include "config_holder.h"
#include <regex>

ConfigHolder::ConfigHolder(){

};
ConfigHolder::~ConfigHolder(){

};
void ConfigHolder::add(const std::string &key, const std::string &value)
{
    //!TODO OPTIMIZE THIS: Trim string
    //!THIS IS OVERKILL
    const std::regex clearSpaces = std::regex("^\\s*(.+)\\s*$");
    std::string valuePost;
    std::smatch match;
    if(std::regex_match(value, match, clearSpaces))
    {
        valuePost = match[1];
    }

    this->config[key] = valuePost;
};
std::string ConfigHolder::get(const std::string &key)
{
    auto it = this->config.find(key);
    if (it != this->config.end())
        return it->second;
    else
        return "";
};

size_t ConfigHolder::size()
{
    return this->config.size();
}