// Copyright 2019
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#include <iostream>
#include <fstream>
#include <tuple>
#include "./Weather.h"

int main(int argc, char** argv) {
  Weather w;

  // Read/create config
  if (std::ifstream("weather.cfg")) {
    if (w.readConfig()) {
      std::cerr << "Invalid config, please check it!" << std::endl;
      exit(1);
    }
  } else {
    w.createDefaultConfig();
    exit(0);
  }

  std::tuple<float, float> values = w.readSensor();
  w.writeSQL(values);
}
