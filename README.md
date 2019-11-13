# SHT20toDB
A simple utility that reads from a SHT20 temperature/humidity sensor and writes the values with a timestamp into a database.

## Dependencies
[MariaDB C++ Connector](https://mariadb.com/kb/en/library/mariadb-connector-c/)  
Ubuntu/Debian: `sudo apt install libmariadb-dev libmariadbclient-dev`  
Arch/Manjaro: `sudo pacman -S mariadb-libs`

## Compile & Run
make
./WeatherMain

## Settings
A file sht20todb.cfg will be created. Enter your DB information in the file.