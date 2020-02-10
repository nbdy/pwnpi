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
#include <sys/queue.h>
#include <tinyb.hpp>
#include "../Configuration/Configuration.h"
#include "../GPS/GPS.h"
#include "../Device/Device.h"


#define BLE_SCAN_TIMEOUT 4

// todo support for multiple hci devices

namespace pwnpi {
    class BluetoothDevice : public Device {
    protected:
        std::string name;
        bool isLE;

    public:
        BluetoothDevice();
        explicit BluetoothDevice(const std::string &address);
        BluetoothDevice(const std::string &address, const std::string &name);
        void setName(const std::string &name);
        std::string getName();
        void setIsLE(bool value);
        bool getIsLE();
    };

    class BluetoothLEDevice : public BluetoothDevice {
    protected:
        std::string className;
        std::string path;
        bool connected;
        uint16_t rssi;

    public:
        BluetoothLEDevice(const std::string& address, const std::string &name, const std::string &className, const std::string &path, bool connected, uint16_t rssi);

        void setClassName(const std::string &value);
        void setPath(const std::string &value);
        void setIsConnected(bool value);

        std::string getClassName();
        std::string getPath();
        bool getIsConnected();
    };
}


static pthread_mutex_t bleMtx = PTHREAD_MUTEX_INITIALIZER;
struct connection_t {
    pthread_t thread;
    char* addr;
    LIST_ENTRY(connection_t) entries;
};

class Bluetooth : public RunnableWithGPS {
private:
    std::string name = "bluetooth";
    bc::BluetoothConfiguration bluetoothConfiguration;

    void *gattAdapter;

    std::vector<pwnpi::BluetoothDevice*> scanClassic();
    std::vector<pwnpi::BluetoothLEDevice*> scanLE();
public:
    explicit Bluetooth(bc::BluetoothConfiguration cfg);
    Bluetooth(bc::BluetoothConfiguration cfg, GPS* gps);

    void run() override;
    void stop() override;
};


#endif //PWNPI_BLUETOOTH_H
