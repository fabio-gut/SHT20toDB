// Copyright 2019
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#include <iostream>
#include <fstream>
#include <tuple>
#include "./SHT20toDB.h"

int main(int argc, char** argv) {
  SHT20toDB s;

  // Read/create config
  if (std::ifstream("SHT20toDB.cfg")) {
    if (s.readConfig()) {
      std::cerr << "Invalid config, please check it!" << std::endl;
      exit(1);
    }
  } else {
    s.createDefaultConfig();
    exit(0);
  }

  std::tuple<float, float> values = s.readSensor();
  s.writeSQL(values);
}
