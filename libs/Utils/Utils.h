//
// Created by insane on 20.01.19.
//

#ifndef PWNPI_UTILS_H
#define PWNPI_UTILS_H

#include <cstdlib>
#include <string>


class StaticUtils {
public:
    static constexpr char chars[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
};

constexpr char StaticUtils::chars[];

class Utils {
    static const char* generateUUID();
};


#endif //PWNPI_UTILS_H
