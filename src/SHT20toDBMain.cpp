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
  // SHT20 sht20(&c);

  std::tuple<float, float> values = std::make_tuple(1.1, 3.3);;

  db.connect();
  db.createTable();
  db.insert(values);
}
