// Copyright 2019
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#ifndef SHT20_H_
#define SHT20_H_

#include "./Config.h"

class SHT20 {
 public:
  explicit SHT20(Config* c);
  float readTemp() const;
  float readHumidity() const;
 private:
  Config* c;
};

#endif  // SHT20_H_
