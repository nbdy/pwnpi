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
#include <gattlib.h>
#include <sys/queue.h>
#include "../Configuration/Configuration.h"
#include "../GPS/GPS.h"
#include "../Device/Device.h"


#define BLE_SCAN_TIMEOUT 4

// todo support for multiple hci devices


class BluetoothDevice : public Device {
protected:
    std::string name;
    bool isLE;

public:
    BluetoothDevice();
    explicit BluetoothDevice(const std::string& address);
    BluetoothDevice(const std::string& address, const std::string& name);

    void setName(const std::string& name);
    std::string getName();

    void setIsLE(bool value);
    bool getIsLE();
};

class BluetoothLEDevice : public BluetoothDevice {
protected:
    bool isLE = true;
};


static pthread_mutex_t bleMtx = PTHREAD_MUTEX_INITIALIZER;
struct connection_t {
    pthread_t thread;
    char* addr;
    LIST_ENTRY(connection_t) entries;
};

class Bluetooth : public RunnableWithGPS {
private:
    std::string name = "blueooth";
    bc::BluetoothConfiguration bluetoothConfiguration;

    void *gattAdapter;
    static void *bleConnectDevice(void *arg);
    static void bleDiscoveredDevice(const char* addr, const char* name);

    std::vector<BluetoothDevice*> scanClassic();
    std::vector<BluetoothLEDevice*> scanLE();


public:
    explicit Bluetooth(bc::BluetoothConfiguration cfg);
    Bluetooth(bc::BluetoothConfiguration cfg, GPS* gps);

    void run() override;
    void stop() override;
};


#endif //PWNPI_BLUETOOTH_H
