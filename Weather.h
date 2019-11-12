// Copyright 2010
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#ifndef WEATHER_H_
#define WEATHER_H_

class Weather {
 public:
  explicit Weather(int adress);
  int adress = 1;  // i2c target adress
  int read() const;
 private:
};

#endif  // WEATHER_H_
