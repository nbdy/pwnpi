//
// Created by insane on 17.01.19.
//

#ifndef PWNPI_MANAGER_H
#define PWNPI_MANAGER_H

#include <thread>
#include "../WiFi/WiFi.h"
#include "../Bluetooth/Bluetooth.h"
#include "../GPS/GPS.h"


class Manager {
private:
    bool doRun = false;

    Configuration* cfg;

    GPS* gps;
    WiFi* wifi;
    Bluetooth* bt;

public:
    explicit Manager(Configuration* cfg);

    void run();

    void setDoRun(bool doRun);
    bool getDoRun();

    void setConfiguration(Configuration* cfg);
    Configuration* getConfiguration();

    void setWiFi(WiFi* wiFi);
    WiFi* getWiFi();

    void setBluetooth(Bluetooth* bluetooth);
    Bluetooth* getBluetooth();

    void setGPS(GPS* gps);
    GPS* getGPS();
};


#endif //PWNPI_MANAGER_H
