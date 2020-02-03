// Copyright 2019
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include <bitset>
#include "./SHT20.h"
#include "./Config.h"
#include "./i2c-dev.h"

const uint16_t POLYNOMIAL = 0x131;  // P(x)=x^8+x^5+x^4+1 = 100110001

// ________________________________________________________________________________

SHT20::SHT20(Config* c) {
  this->c = c;
  if ((this->fd = open(this->c->busFile.c_str(), O_RDWR)) < 0) {  // open bus
    std::cerr << "SHT20  : Cannot open bus file" << std::endl;
    exit(1);
  }
  if (ioctl(this->fd, I2C_SLAVE, this->c->i2cAddress) < 0) {  // set i2c address
    std::cerr << "SHT20  : Cannot set slave address" << std::endl;
    exit(1);
  }
  usleep(1000);
}

// ________________________________________________________________________________

SHT20::~SHT20() {
  close(this->fd);  // close bus file
}

// ________________________________________________________________________________

float SHT20::getTemp() const {
  uint32_t fullRead;
  uint16_t tempData;

  i2c_smbus_write_byte(this->fd, 0xf3);  // trigger T measurement 11110011
  usleep(100000);

  if (read(this->fd, &fullRead, 3) != 3) {
    std::cerr << "SHT20  : Error reading temp from sensor" << std::endl;
    return 999999.0;
  }

  tempData = fullRead;  // first 16 bits
  uint8_t checksum = fullRead >> 16;  // bits 16-24

  if (getCRC(tempData) != checksum) {
    std::cout << "SHT20  : Checksum does not match" << std::endl;
    return 999999.0;
  }

  return -46.85 + 175.72 * ntohs(tempData) / pow(2, 16);
}

// ________________________________________________________________________________

float SHT20::getHumidity() const {
  uint32_t fullRead;
  uint16_t humidityData;

  i2c_smbus_write_byte(this->fd, 0xf5);  // trigger RH measurement 11110101
  usleep(100000);

  if (read(this->fd, &fullRead, 3) != 3) {
    std::cerr << "SHT20  : Error reading humidity from sensor" << std::endl;
    return 999999.0;
  }

  humidityData = fullRead;
  uint8_t checksum = fullRead >> 16;

  if (getCRC(humidityData) != checksum) {
    std::cout << "SHT20  : Checksum does not match" << std::endl;
    return 999999.0;
  }

  return -6 + 125 * ntohs(humidityData) / pow(2, 16);
}

// ________________________________________________________________________________

uint8_t SHT20::getCRC(uint16_t data) const {
  uint8_t crc = 0;

  uint8_t data_a[2];
  data_a[0] = (uint8_t)data;
  data_a[1] = (uint8_t)(data >> 8);

  for (int byteCtr = 0; byteCtr < 2; ++byteCtr) {
    crc ^= (data_a[byteCtr]);
    for (uint8_t bit = 8; bit > 0; --bit) {
      if (crc & 0x80)
        crc = (crc << 1) ^ POLYNOMIAL;
      else
        crc = (crc << 1);
    }
  }
  return crc;
}
