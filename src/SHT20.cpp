// Copyright 2019
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include "./SHT20.h"
#include "./Config.h"
#include "./i2c-dev.h"

// ________________________________________________________________________________

SHT20::SHT20(Config* c) {
  this->c = c;

  this->fd = open(this->c->busFile.c_str(), O_RDWR);
  if (this->fd < 0)
    std::cerr << "SHT20  : Cannot open bus" << std::endl;
  else
    std::cout << "SHT20  : Bus open" << std::endl;
  ioctl(this->fd, I2C_SLAVE, this->c->i2cAddress);
  usleep(1000);
}

// ________________________________________________________________________________

float SHT20::getTemp() const {
  uint16_t tempData;
  i2c_smbus_write_byte(this->fd, 0xf3);  // trigger T measurement 11110011
  usleep(100000);
  if (read(this->fd, &tempData, sizeof(tempData)) != 2) {
    std::cerr << "SHT20  : Error reading temp from sensor" << std::endl;
    return 999999.0;
  }
  return -6 + 125 * ntohs(tempData) / pow(2, 16);
}

// ________________________________________________________________________________

float SHT20::getHumidity() const {
  uint16_t humidityData;
  i2c_smbus_write_byte(this->fd, 0xf5);  // trigger RH measurement 11110101
  usleep(100000);
  if (read(this->fd, &humidityData, sizeof(humidityData)) != 2) {
    std::cerr << "SHT20  : Error reading humidity from sensor" << std::endl;
    return 999999.0;
  }
  return -46.85 + 157.72 * ntohs(humidityData) / pow(2, 16);
}
