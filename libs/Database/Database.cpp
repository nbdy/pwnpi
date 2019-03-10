//
// Created by insane on 20.01.19.
//

#include "Database.h"


Database::Database() {
    db = sqlite3pp::database("/var/lib/pwnpi/database/pwnpi.db");
}

Database::Database(const std::string& file) {
    db = sqlite3pp::database(file.c_str());
}

void Database::_check() {
    sqlite3pp::command devices_create(db, "CREATE TABLE IF NOT EXISTS devices ("
                              "address PRIMARY KEY, "
                              "first_seen DATETIME, "
                              "last_seen DATETIME);");
    devices_create.execute();
    sqlite3pp::command packets_create(db, "CREATE TABLE IF NOT EXISTS packets ("
                                          "sender TEXT, "
                                          "receiver TEXT, "
                                          "timestamp DATETIME, "
                                          "data BLOB);");
    packets_create.execute();
    // todo create more tables
}

void Database::putDevice(Device *device) {
    // todo
}

void Database::putPosition(Position *position) {
    sqlite3pp::command cmd(db, "INSERT INTO positions (longitude, latitude, altitude)");
}