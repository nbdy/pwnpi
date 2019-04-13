//
// Created by insane on 20.01.19.
//

#ifndef PWNPI_DEVICE_H
#define PWNPI_DEVICE_H


#include <string>
#include <tins/tins.h>

class Device {
protected:
    std::string address;

public:
    Device(){};
    explicit Device(const std::string& address);

    void setAddress(const std::string& address);
    std::string getAddress();
};

#endif //PWNPI_DEVICE_H
