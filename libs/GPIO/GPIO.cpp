//
// Created by insane on 20.01.19.
//

#include <sys/stat.h>
#include <fstream>
#include "GPIO.h"


bool GPIOStatic::isPi() {
    struct stat buf;
    return (stat ("/proc/device-tree/model", &buf) == 0);
}

const char* GPIOStatic::manufactureValuePath(uint8_t pin) {
    std::string p = GPIOStatic::manipulationPath + std::to_string(pin) + GPIOStatic::value;
    return p.c_str();
}


GPIO::GPIO() {
    this->pin = 4;
    _export();
}

GPIO::GPIO(uint8_t pin) {
    this->pin = pin;
    _export();
}

void GPIO::_export() {
    std::ofstream e(GPIOStatic::exportPath);
    e << std::to_string(pin);
    e.close();
}

void GPIO::_unexport() {
    std::ofstream e(GPIOStatic::unexportPath);
    e << std::to_string(pin);
    e.close();
}

uint8_t GPIO::getPin() {
    return pin;
}

void GPIO::setPin(uint8_t pin) {
    this->pin = pin;
}

void GPIO::setDirection(const char *direction) {
    std::string p = GPIOStatic::manipulationPath + std::to_string(pin) + GPIOStatic::direction;
    std::ofstream e(p.c_str());
    e << direction;
    e.close();
}

void GPIO::setValue(uint8_t val) {
    std::ofstream e(GPIOStatic::manufactureValuePath(pin));
    e << val;
    e.close();
}

bool GPIO::getValue() {
    std::ifstream e(GPIOStatic::manufactureValuePath(pin));
    std::string val;
    e >> val;
    e.close();
    return val == "1";
}

void GPIO::watchForHigh(void *cb) {
    // todo
}

void GPIO::watchForLow(void *cb) {
    // todo
}

void GPIO::setDirectionIn() {
    setDirection(GPIOStatic::directionIn);
}

void GPIO::setDirectionOut() {
    setDirection(GPIOStatic::directionOut);
}

GPIO::~GPIO() {
    _unexport();
}