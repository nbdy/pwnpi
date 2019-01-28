//
// Created by insane on 20.01.19.
//

#ifndef PWNPI_DEVICE_H
#define PWNPI_DEVICE_H


#include <string>
#include <tins/tins.h>

class Device {
private:
    std::string address;
    std::string receiver;
    uint8_t type;

public:
    Device();
    Device(Tins::Dot11 dot11, bool src); // else dst (duh)
};

class TX : public Device {

};

class RX : public Device {

};

#endif //PWNPI_DEVICE_H
