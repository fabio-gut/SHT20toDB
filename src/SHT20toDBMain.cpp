// Copyright 2019
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#include <iostream>
#include <tuple>
#include "./Config.h"
#include "./DB.h"
#include "./SHT20.h"

// ________________________________________________________________________________

int main(int argc, char** argv) {
  Config c;
  DB db(&c);
  SHT20 sht20(&c);

  float temp = sht20.getTemp();
  float humidity = sht20.getHumidity();

  if (temp == 999999.0 || humidity == 999999.0) {
    std::cerr << "Failed to read values. Stopping" << std::endl;
    exit(1);
  } else {
    std::cout << "Got values from sensor: T=" << temp << " °C, RH="
    << humidity << " %" << std::endl;
  }

  db.connect();
  db.createTable();
  db.insert(std::make_tuple(temp, humidity));
  std::cout << "Inserted values into DB" << std::endl;
}
