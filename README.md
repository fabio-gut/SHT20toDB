# SHT20toDB
A simple tool that reads from a [SHT20](https://www.mouser.com/datasheet/2/682/Sensirion_Humidity_Sensors_SHT20_Datasheet-1274196.pdf) temperature/humidity sensor and writes the values with a timestamp into a database.

## Dependencies
[MariaDB C++ Connector](https://mariadb.com/kb/en/library/mariadb-connector-c/)  
Ubuntu/Debian: `sudo apt install libmariadb-dev libmariadbclient-dev`  
Arch/Manjaro: `sudo pacman -S mariadb-libs`

## Compile & Run
`make`  
`./SHT20toDBMain` (You can rename the file just like you want)

## Settings
A file SHT20toDB.cfg will be created. Enter your DB information in the file.