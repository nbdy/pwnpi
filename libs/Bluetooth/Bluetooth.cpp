//
// Created by insane on 17.01.19.
//

#include <iostream>
#include "Bluetooth.h"

pwnpi::BluetoothDevice::BluetoothDevice() {this->isLE = false;}

pwnpi::BluetoothDevice::BluetoothDevice(const std::string &address) {this->address = address; this->isLE = false;}

pwnpi::BluetoothDevice::BluetoothDevice(const std::string &address, const std::string &name) {this->address = address; this->name = name; isLE=false;}

void pwnpi::BluetoothDevice::setName(const std::string &value) {this->name = value;}

std::string pwnpi::BluetoothDevice::getName() {return this->name;}

void pwnpi::BluetoothDevice::setIsLE(bool value) {this->isLE = value;}

bool pwnpi::BluetoothDevice::getIsLE() {return this->isLE;}

pwnpi::BluetoothLEDevice::BluetoothLEDevice(const std::string &address, const std::string &name,
                                            const std::string &className, const std::string &path, bool connected, uint16_t rssi) {
    this->address = address;
    this->name = name;
    this->className = className;
    this->path = path;
    this->connected = connected;
    this->rssi = rssi;
    setIsLE(true);
}

void pwnpi::BluetoothLEDevice::setIsConnected(bool value) {connected = value;}

void pwnpi::BluetoothLEDevice::setPath(const std::string &value) { this->path = value;}

void pwnpi::BluetoothLEDevice::setClassName(const std::string &value) { this->className = value;}

std::string pwnpi::BluetoothLEDevice::getPath() {return path;}

bool pwnpi::BluetoothLEDevice::getIsConnected() {return connected;}

std::string pwnpi::BluetoothLEDevice::getClassName() {return className;}

Bluetooth::Bluetooth(bc::BluetoothConfiguration cfg) {
    bluetoothConfiguration = std::move(cfg);
    this->setGPS(new GPS());
    setDoRun(bluetoothConfiguration.enable);
}

Bluetooth::Bluetooth(bc::BluetoothConfiguration cfg, GPS *gps) {
    bluetoothConfiguration = std::move(cfg);
    this->setGPS(gps);
    setDoRun(bluetoothConfiguration.enable);
}

std::vector<pwnpi::BluetoothDevice*> Bluetooth::scanClassic() {
    std::vector<pwnpi::BluetoothDevice*> devices;
    inquiry_info* ii = nullptr;
    int maxRsp, numRsp, devId, sck, len, flags, i;
    char addr[19] = {0};
    char _name[248] = {0};
    devId = hci_get_route(nullptr);
    sck = hci_open_dev(devId);
    if(devId < 0 || sck < 0) return devices;
    len = 8;
    maxRsp = 255;
    flags = IREQ_CACHE_FLUSH;
    ii = (inquiry_info*) malloc(maxRsp * sizeof(inquiry_info));
    numRsp = hci_inquiry(devId, len, maxRsp, nullptr, &ii, flags);
    for (i = 0; i < numRsp; i++) {
        ba2str(&(ii+i)->bdaddr, addr);
        memset(_name, 0, sizeof(_name));
        if (hci_read_remote_name(sck, &(ii+i)->bdaddr, sizeof(_name), _name, 0) < 0) strcpy(_name, "[unknown]");
        devices.emplace_back(new pwnpi::BluetoothDevice(addr, _name));
    }
    free(ii);
    close(sck);
    return devices;
}

std::vector<pwnpi::BluetoothLEDevice*> Bluetooth::scanLE() {
    std::cout << "scanning bluetooth le" << std::endl;
    std::vector<pwnpi::BluetoothLEDevice*> devices;
    BluetoothManager *manager = nullptr;
    try {
        manager = BluetoothManager::get_bluetooth_manager();
    } catch (const std::runtime_error& e){
        std::cerr << e.what() << std::endl;
        return devices;
    }
    if(!manager->start_discovery()) return devices;
    for(int i=0; i<5; i++){
        auto lst = manager->get_devices();
        for(auto & it : lst){
            devices.emplace_back(new pwnpi::BluetoothLEDevice(
                    it->get_address(),
                    it->get_name(),
                    it->get_class_name(),
                    it->get_object_path(),
                    it->get_connected(),
                    it->get_rssi()
                    ));
        }
        std::this_thread::sleep_for(std::chrono::seconds(4));
    }
    manager->stop_discovery();
    return devices;
}

void Bluetooth::stop() {
    setDoRun(false);
    pthread_mutex_unlock(&bleMtx);
}

void Bluetooth::run() {
    while(this->getDoRun()){
        if(!bluetoothConfiguration.onlyLE || bluetoothConfiguration.onlyClassic) {
            std::vector<pwnpi::BluetoothDevice*> cDevices = scanClassic();
            std::cout << "found " << cDevices.size() << " classic devices" << std::endl;
        }
        if(!bluetoothConfiguration.onlyClassic || bluetoothConfiguration.onlyLE) {
            std::vector<pwnpi::BluetoothLEDevice*> lDevices = scanLE();  // todo retry on disconnected / errorous devices
            std::cout << "found " << lDevices.size() << " le devices" << std::endl;
        }
    }
}