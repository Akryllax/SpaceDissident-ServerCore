#include "config_reader.h"

ConfigReader::ConfigReader(std::filesystem::path path)
{

};

ConfigReader::ConfigReader(std::string path)
{
    if(std::filesystem::exists(path))
    {
        this->_filepath = std::filesystem::path(path);
    } else {

    }
};
