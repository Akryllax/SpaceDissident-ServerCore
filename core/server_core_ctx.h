#pragma once
#include <any>
#include <map>
#include <string>

class ServerContext : public std::map<std::string, std::any>
{

};