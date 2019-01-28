//
// Created by insane on 20.01.19.
//

#ifndef PWNPI_DATABASE_H
#define PWNPI_DATABASE_H

#include <redox.hpp>
#include "../Json/json.hpp"
#include "../Device/Device.h"


using json = nlohmann::json;

class Database {
private:
    redox::Redox rdx;

public:
    Database(char* host, int port);
    Database(std::string host, int port);

    void putDevice(Device* device);

};


#endif //PWNPI_DATABASE_H
