//
// Created by insane on 20.01.19.
//

#include "Device.h"


Device::Device(const std::string &address) {
    this->address = address;
}

std::string Device::getAddress() { return address; }

void Device::setAddress(const std::string &address) {this->address = address;}