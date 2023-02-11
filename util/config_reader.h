#pragma once
#include "spdlog/spdlog.h"
#include <filesystem>
#include <string>

class ConfigReader
{
protected:
  std::filesystem::path _configPath;

public:
  ConfigReader(std::string path);
  ConfigReader(std::filesystem::path path);

  bool parseConfiguration();
  bool validate();
  bool saveConfiguration();
};
