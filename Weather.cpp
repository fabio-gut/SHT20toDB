// Copyright 2010
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include "./Weather.h"

// ________________________________________________________________________________

std::tuple<float, float> Weather::readSensor() const {
  std::cout << "Reading sensor..." << std::endl;
  return std::make_tuple(1.1, 3.3);
}

// ________________________________________________________________________________

void Weather::writeSQL(std::tuple<float, float> values) {
  std::cout << "Writing to DB..." << std::endl;
  std::cout << std::get<0>(values) << std::endl;
}

// ________________________________________________________________________________

void Weather::createDefaultConfig() const {
  std::cout << "No config found, creating default. "
               "Please edit the config and restart!" << std::endl;

  std::string text("i2cAdress=1\n"
                   "sqlHost=localhost\n"
                   "sqlUser=user\n"
                   "sqlPass=pass\n"
                   "sqlDB=database\n");

  std::ofstream configFile("weather.cfg");
  configFile << text;
  configFile.close();
}

// ________________________________________________________________________________

int Weather::readConfig() {
  std::cout << "Reading config..." << std::endl;

  std::ifstream configFile("weather.cfg");
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

// ________________________________________________________________________________
