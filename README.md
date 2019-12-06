# SHT20toDB
[badge](https://github.com/fabio-gut/SHT20toDB/workflows/C/C++%20CI/badge.svg)
A simple tool that reads from a [SHT20](https://www.mouser.com/datasheet/2/682/Sensirion_Humidity_Sensors_SHT20_Datasheet-1274196.pdf) temperature/humidity sensor and writes the values with a timestamp into a database.

## Dependencies
[MariaDB C++ Connector](https://mariadb.com/kb/en/library/mariadb-connector-c/)  
* Ubuntu/Debian: `sudo apt install libmariadb-dev libmariadbclient-dev`  
* Arch/Manjaro: `sudo pacman -S mariadb-libs`

<!---I2C Development Headers
* Ubuntu/Debian: `sudo apt install libi2c-dev`
* Arch/Manjaro:  `sudo pacman -S i2c-tools linux-api-headers`-->

## Compile & Run
`make`  
`./SHT20toDB`

## Settings
A file SHT20toDB.cfg will be created in the folder you execute the binary in. Enter your DB information in the file.
