//
// Created by insane on 20.01.19.
//

#ifndef PWNPI_GPIO_H
#define PWNPI_GPIO_H

#include <cstdint>


class GPIOStatic {
public:
    static constexpr char exportPath[23] = "/sys/class/gpio/export";
    static constexpr char unexportPath[25] = "/sys/class/gpio/unexport";
    static constexpr char manipulationPath[21] = "/sys/class/gpio/gpio";
    static constexpr char direction[11] = "/direction";
    static constexpr char value[7] = "/value";

    static constexpr char directionIn[3] = "in";
    static constexpr char directionOut[4] = "out";

    static bool isPi();
    static const char* manufactureValuePath(uint8_t pin);
};

constexpr char GPIOStatic::exportPath[];
constexpr char GPIOStatic::unexportPath[];
constexpr char GPIOStatic::manipulationPath[];
constexpr char GPIOStatic::direction[];
constexpr char GPIOStatic::value[];
constexpr char GPIOStatic::directionIn[];
constexpr char GPIOStatic::directionOut[];

class GPIO {
private:
    uint8_t pin;

    void _export();
    void _unexport();

public:
    GPIO();
    explicit GPIO(uint8_t pin);

    void setDirection(const char* direction);
    void setDirectionIn();
    void setDirectionOut();

    void setPin(uint8_t pin);
    uint8_t getPin();

    bool getValue();
    void setValue(uint8_t val);

    void watchForHigh(void* cb);
    void watchForLow(void* cb);

    ~GPIO();
};


#endif //PWNPI_GPIO_H
