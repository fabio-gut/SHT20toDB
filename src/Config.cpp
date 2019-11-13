// Copyright 2019
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "./Config.h"

// ________________________________________________________________________________

Config::Config() {
  if (this->exists()) {
    if (this->read()) {
      std::cerr << "Config : Parsing failed, please check it" << std::endl;
      exit(1);
    } else {
      std::cout << "Config : Parsing successful" << std::endl;
    }
  } else {
    std::cout << "Config : Not found, creating default"
                 "Please edit the config and restart!" << std::endl;
    this->createDefault();
  }
}

// ________________________________________________________________________________

void Config::createDefault() const {
  std::string text("i2cAdress=1\n"
                   "sqlHost=localhost\n"
                   "sqlUser=user\n"
                   "sqlPass=pass\n"
                   "sqlDB=database\n");

  std::ofstream configFile(this->name);
  configFile << text;
  configFile.close();
}

// ________________________________________________________________________________

bool Config::exists() const {
  std::ifstream f(this->name);
  return f.good();
}

// ________________________________________________________________________________

int Config::read() {
  std::ifstream configFile(this->name);
  std::string line;
  while (true) {
    std::getline(configFile, line);
    if (configFile.eof()) { break; }

    std::istringstream is_line(line);
    std::string key;
    if (std::getline(is_line, key, '=')) {
      std::string value;
      if (std::getline(is_line, value)) {
        if (key == "i2cAdress")
          this->i2cAdress = atoi(value.c_str());
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
