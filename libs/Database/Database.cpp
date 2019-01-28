//
// Created by insane on 20.01.19.
//

#include "Database.h"

Database::Database(char* host, int port) {
    rdx.connect(host, port);
}

Database::Database(std::string host, int port) {
    rdx.connect(host, port);
}

void Database::putDevice(Device *device) {
    // todo
}