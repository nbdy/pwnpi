//
// Created by insane on 20.01.19.
//

#ifndef PWNPI_DATABASE_H
#define PWNPI_DATABASE_H

#include "../Json/json.hpp"
#include "../../sqlite3pp/headeronly_src/sqlite3pp.h"
#include "../Device/Device.h"
#include "../GPS/GPS.h"
#include "../Packet/Packet.h"


using json = nlohmann::json;

class Database {
private:
    sqlite3pp::database db;

    void _check();

public:
    Database();
    explicit Database(const std::string& file);

    void putDevice(Device* device);
    void putPosition(Position* position);
    void putPacket(Packet* packet);
};


#endif //PWNPI_DATABASE_H
