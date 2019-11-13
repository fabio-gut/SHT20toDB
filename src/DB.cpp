// Copyright 2019
// Author: Fabio Gutmann <https://github.com/fabio-gut>

#include <mysql.h>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <tuple>
#include "./DB.h"
#include "./Config.h"

// ________________________________________________________________________________

DB::DB(Config* c) {
  this->mysql = mysql_init(NULL);
  this->c = c;
}

// ________________________________________________________________________________

DB::~DB() {
  mysql_close(this->mysql);
  std::cout << "DB     : Connection closed" << std::endl;
}

// ________________________________________________________________________________

void DB::connect() const {
  if (!mysql_real_connect(this->mysql, this->c->sqlHost.c_str(),
                          this->c->sqlUser.c_str(), this->c->sqlPass.c_str(),
                          this->c->sqlDB.c_str(), 0, "/tmp/mysql.sock", 0)) {
    std::cerr << "DB     : Connection failed" << std::endl;
    exit(1);
  } else {
    std::cout << "DB     : Connected" << std::endl;
  }
}

// ________________________________________________________________________________

void DB::insert(const std::tuple<float, float>& values) const {
  float t = std::get<0>(values);
  float h = std::get<1>(values);

  // Get time and date
  std::time_t time = std::time(nullptr);
  std::tm* now = std::localtime(&time);

  std::stringstream ssd;
  ssd << (now->tm_year + 1900) << "-" << (now->tm_mon + 1)
      << "-" << now->tm_mday;
  std::string date = ssd.str();

  std::stringstream sst;
  sst << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
  std::string time_s = sst.str();

  // Insert values
  std::stringstream ss;
  ss << "INSERT INTO weather VALUES ('" << date << "', '" << time_s << "', '"
     << t << "', '" << h << "')";
  std::string query(ss.str());

  if (this->execute(query))
    std::cout << "DB     : Inserted T=" << t << " H=" << h << std::endl;
  else
    std::cerr << "DB     : Failed to insert T=" << t << " H=" << h << std::endl;
}

// ________________________________________________________________________________

void DB::createTable() const {
  // Create table if not exists
  std::string query("CREATE TABLE IF NOT EXISTS weather (date TINYTEXT, "
                    "time TINYTEXT, temp FLOAT(2), humidity FLOAT(2))");
  if (this->execute(query))
    std::cout << "DB     : Found/created table" << std::endl;
  else
    std::cerr << "DB     : Could not create table" << std::endl;
}

// ________________________________________________________________________________

bool DB::execute(const std::string& query) const {
  if (mysql_real_query(this->mysql, query.c_str(), query.length()))
    return false;
  else
    return true;
}
