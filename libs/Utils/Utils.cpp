//
// Created by insane on 20.01.19.
//

#include "Utils.h"


const char* Utils::generateUUID() {
    std::string u = std::string(36,' ');
    int r = 0;

    u[8] = '-';
    u[13] = '-';
    u[18] = '-';
    u[23] = '-';

    u[14] = '4';

    for(int i=0;i<36;i++){
        if (i != 8 && i != 13 && i != 18 && i != 14 && i != 23) {
            if (r <= 0x02) {
                r = 0x2000000 + (std::rand() * 0x1000000) | 0;
            }
            r >>= 4;
            u[i] = StaticUtils::chars[(i == 19) ? ((r & 0xf) & 0x3) | 0x8 : r & 0xf];
        }
    }
    return u.c_str();
}