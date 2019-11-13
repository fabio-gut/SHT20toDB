// Copyright 2019
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#ifndef DB_H_
#define DB_H_

#include <mysql.h>
#include <tuple>
#include <string>
#include "./Config.h"

class DB {
 public:
  explicit DB(Config* c);
  ~DB();
  void connect() const;
  void createTable() const;
  void insert(const std::tuple<float, float>& values) const;
 private:
  Config* c;
  MYSQL* mysql;
  bool execute(const std::string& query) const;
};

#endif  // DB_H_
