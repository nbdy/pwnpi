cmake_minimum_required(VERSION 3.10)
project(pwnpi)

set(CMAKE_CXX_STANDARD 11)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.63 COMPONENTS log log_setup REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

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
        libs/Utils/Utils.h libs/Packet/Packet.cpp libs/Packet/Packet.h)

target_link_libraries(pwnpi tins ev pthread gps bluetooth hiredis redox ${Boost_LIBRARIES})