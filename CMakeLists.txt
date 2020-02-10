cmake_minimum_required(VERSION 3.2)
project(pwnpi)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        ${tinyb_LIB_INCLUDE_DIRS}
)

add_executable(pwnpi
        main.cpp
        libs/Configuration/Configuration.cpp
        libs/Configuration/Configuration.h
        libs/WiFi/WiFi.cpp libs/WiFi/WiFi.h
        libs/Manager/Manager.cpp
        libs/Manager/Manager.h
        libs/Bluetooth/Bluetooth.cpp
        libs/Bluetooth/Bluetooth.h
        libs/GPS/GPS.cpp
        libs/GPS/GPS.h
        libs/Runnable/Runnable.cpp
        libs/Runnable/Runnable.h
        libs/GPIO/GPIO.cpp
        libs/GPIO/GPIO.h
        libs/Database/Database.cpp
        libs/Database/Database.h
        libs/Device/Device.cpp
        libs/Device/Device.h
        libs/Utils/Utils.cpp
        libs/Utils/Utils.h
        libs/Packet/Packet.cpp
        libs/Packet/Packet.h)

target_link_libraries(pwnpi tins ev pthread gps bluetooth sqlite3 tinyb)

install(DIRECTORY DESTINATION /var/lib/pwnpi/database/)
install(DIRECTORY DESTINATION /var/lib/pwnpi/)

