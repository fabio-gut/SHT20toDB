// Copyright 2010
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#ifndef WEATHER_H_
#define WEATHER_H_

#include <string>
#include <tuple>

class Weather {
 public:
  int adress = 1;  // i2c target adress
  std::tuple<float, float> readSensor() const;
  void writeSQL(std::tuple<float, float> values);
  void createDefaultConfig() const;
  int readConfig();
 private:
  int i2cAdress;
  std::string sqlHost;
  std::string sqlUser;
  std::string sqlPass;
  std::string sqlDB;
};

#endif  // WEATHER_H_
