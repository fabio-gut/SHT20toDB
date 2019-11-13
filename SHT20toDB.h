// Copyright 2010
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#ifndef SHT20TODB_H_
#define SHT20TODB_H_

#include <string>
#include <tuple>

class SHT20toDB {
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

#endif  // SHT20TODB_H_
