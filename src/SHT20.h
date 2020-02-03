// Copyright 2019
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#ifndef SHT20_H_
#define SHT20_H_

#include "./Config.h"

class SHT20 {
 public:
  explicit SHT20(Config* c);
  ~SHT20();
  float getTemp() const;
  float getHumidity() const;
  uint8_t getCRC(uint16_t data) const;
 private:
  Config* c;
  int fd = -1;  // File descriptor to access sensor
};

#endif  // SHT20_H_
