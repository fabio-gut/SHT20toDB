// Copyright 2019
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#include "./SHT20.h"
#include "./Config.h"

// ________________________________________________________________________________

SHT20::SHT20(Config* c) {
  this->c = c;
}

// ________________________________________________________________________________

float SHT20::readTemp() const {
}

// ________________________________________________________________________________

float SHT20::readHumidity() const {
}
