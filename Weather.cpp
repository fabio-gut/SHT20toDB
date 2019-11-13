// Copyright 2010
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#include <mysql.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <ctime>
#include "./Weather.h"


// ________________________________________________________________________________

std::tuple<float, float> Weather::readSensor() const {
  std::cout << "Reading sensor..." << std::endl;
  return std::make_tuple(1.1, 3.3);
}

// ________________________________________________________________________________

void Weather::writeSQL(std::tuple<float, float> values) {
  std::cout << "Writing to DB..." << std::endl;
  // std::cout << std::get<0>(values) << std::endl;

  std::time_t t = std::time(nullptr);
  std::tm* now = std::localtime(&t);

  std::stringstream ssd;
  ssd << (now->tm_year + 1900) << "-" << (now->tm_mon + 1)
      << "-" << now->tm_mday;
  std::string date = ssd.str();

  std::stringstream sst;
  sst << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
  std::string time = sst.str();

  MYSQL *mysql;
  std::string query;
  MYSQL_RES *result;

  // Establish connection
  mysql = mysql_init(NULL);
  if (!mysql_real_connect(mysql, this->sqlHost.c_str(), this->sqlUser.c_str(),
                          this->sqlPass.c_str(), this->sqlDB.c_str(),
                          0, "/tmp/mysql.sock", 0)) {
    std::cout << "Connection failed" << std::endl;
  } else {
    std::cout << "Connected" << std::endl;
  }

  // Create table if not exists
  query = "CREATE TABLE IF NOT EXISTS weather (date TINYTEXT, time TINYTEXT, "
          "temp FLOAT(2), humidity FLOAT(2))";
  if (mysql_real_query(mysql, query.c_str(), query.length())) {
    std::cout << "Error with command" << std::endl;
  } else {
    std::cout << "Worked" << std::endl;
  }

  // Insert values
  std::stringstream ss;
  ss << "INSERT INTO weather VALUES ('" << date << "', '" << time << "', '"
     << std::get<0>(values) << "', '" << std::get<1>(values) << "')";
  query = ss.str();
  std::cout << query << std::endl;
  if (mysql_real_query(mysql, query.c_str(), query.length())) {
    std::cout << "Error with command" << std::endl;
  } else {
    std::cout << "Worked" << std::endl;
  }

  mysql_close(mysql);
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
