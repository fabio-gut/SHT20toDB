// Copyright 2019
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

class Config {
 public:
  Config();
  bool exists() const;
  void createDefault() const;
  int read();

  int i2cAdress;
  std::string sqlHost;
  std::string sqlUser;
  std::string sqlPass;
  std::string sqlDB;
 private:
  std::string name = "SHT20toDB.cfg";
};

#endif  // CONFIG_H_