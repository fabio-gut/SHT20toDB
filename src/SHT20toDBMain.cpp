// Copyright 2019
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#include <unistd.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <tuple>
#include "./Config.h"
#include "./DB.h"
#include "./SHT20.h"

// ________________________________________________________________________________

int main(int argc, char** argv) {
  Config c;
  DB db(&c);
  SHT20 sht20(&c);

  float temp;
  float humidity;
  int tries = 0;

  while ((temp = sht20.getTemp()) == 999999.0) {
    if (tries > 10) {
      std::cerr << "Failed to read values. Stopping" << std::endl;
      exit(1);
    }
    tries++;
    usleep(100000);
  }

  while ((humidity = sht20.getHumidity()) == 999999.0) {
    if (tries > 10) {
      std::cerr << "Failed to read values. Stopping" << std::endl;
      exit(1);
    }
    tries++;
    usleep(100000);
  }

  std::cout << "Got values from sensor: T=" << temp << " °C, RH="
    << humidity << " %" << std::endl;

  db.connect();
  db.createTable();
  db.insert(std::make_tuple(temp, humidity));
  std::cout << "Inserted values into DB" << std::endl;
}
