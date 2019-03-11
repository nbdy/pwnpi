//
// Created by insane on 17.01.19.
//

#ifndef PWNPI_BLUETOOTH_H
#define PWNPI_BLUETOOTH_H


#include <thread>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include "../Configuration/Configuration.h"
#include "../GPS/GPS.h"

class Bluetooth : public RunnableWithGPS {
private:
    std::string name = "blueooth";
    bc::BluetoothConfiguration bluetoothConfiguration;

public:
    explicit Bluetooth(bc::BluetoothConfiguration cfg);
    Bluetooth(bc::BluetoothConfiguration cfg, GPS* gps);

    void run();
};


#endif //PWNPI_BLUETOOTH_H
