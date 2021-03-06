// Copyright 2019
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#include <unistd.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "./Config.h"

// ________________________________________________________________________________

Config::Config() {
  char exepath[100] = {0};
  std::stringstream dir;
  dir << "/proc/" << getpid() << "/exe";
  readlink(dir.str().c_str(), exepath, sizeof(exepath));
  this->configPath.append(exepath);
  this->configPath.append(".cfg");

  if (this->exists()) {
    if (this->read()) {
      std::cerr << "Config : Parsing failed, please check it" << std::endl;
      exit(1);
    }
  } else {
    std::cerr << "Config : Not found, creating default" << std::endl;
    std::cerr << "Please edit the config and restart!" << std::endl;
    this->createDefault();
    exit(1);
  }
}

// ________________________________________________________________________________

void Config::createDefault() const {
  std::string text("i2cAddress=64\n"
                   "busFile=/dev/i2c-1\n"
                   "sqlHost=localhost\n"
                   "sqlUser=user\n"
                   "sqlPass=pass\n"
                   "sqlDB=database\n");

  std::ofstream configFile(this->configPath);
  configFile << text;
  configFile.close();
}

// ________________________________________________________________________________

bool Config::exists() const {
  std::ifstream f(this->configPath);
  return f.good();
}

// ________________________________________________________________________________

int Config::read() {
  std::ifstream configFile(this->configPath);
  std::string line;
  while (true) {
    std::getline(configFile, line);
    if (configFile.eof()) { break; }

    std::istringstream is_line(line);
    std::string key;
    if (std::getline(is_line, key, '=')) {
      std::string value;
      if (std::getline(is_line, value)) {
        if (key == "i2cAddress")
          this->i2cAddress = atoi(value.c_str());
        else if (key == "busFile")
          this->busFile = value;
        else if (key == "sqlHost")
          this->sqlHost = value;
        else if (key == "sqlUser")
          this->sqlUser = value;
        else if (key == "sqlPass")
          this->sqlPass = value;
        else if (key == "sqlDB")
          this->sqlDB = value;
        else
          return 1;
      } else {
      return 1;
      }
    }
  }
  return 0;
}
