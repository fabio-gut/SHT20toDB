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

  uint8_t i2cAddress;
  std::string busFile;
  std::string sqlHost;
  std::string sqlUser;
  std::string sqlPass;
  std::string sqlDB;
 private:
  std::string configPath;
};

#endif  // CONFIG_H_
