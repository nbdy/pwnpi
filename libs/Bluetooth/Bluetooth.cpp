//
// Created by insane on 17.01.19.
//

#include <iostream>
#include "Bluetooth.h"

BluetoothDevice::BluetoothDevice() {

}

BluetoothDevice::BluetoothDevice(const std::string &address) {this->address = address;}

BluetoothDevice::BluetoothDevice(const std::string &address, const std::string &name) {this->address = address; this->name = name;}

void BluetoothDevice::setName(const std::string &name) {this->name = name;}

std::string BluetoothDevice::getName() {return this->name;}

void BluetoothDevice::setIsLE(bool value) {this->isLE = value;}

bool BluetoothDevice::getIsLE() {return this->isLE;}

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

std::vector<BluetoothDevice*> Bluetooth::scanClassic() {
    std::vector<BluetoothDevice*> devices;
    inquiry_info* ii = nullptr;
    int maxRsp, numRsp, devId, sck, len, flags, i;
    char addr[19] = {0};
    char name[248] = {0};
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
        memset(name, 0, sizeof(name));
        if (hci_read_remote_name(sck, &(ii+i)->bdaddr, sizeof(name), name, 0) < 0) strcpy(name, "[unknown]");
        devices.emplace_back(new BluetoothDevice(addr, name));
    }
    free(ii);
    close(sck);
    return devices;
}


LIST_HEAD(listhead, connection_t) bleConnections;

void *Bluetooth::bleConnectDevice(void *arg) {
    struct connection_t *connection = (connection_t*) arg;
    char* addr = connection->addr;
    gatt_connection_t* gatt_connection;
    gattlib_primary_service_t* services;
    gattlib_characteristic_t* characteristics;
    int services_count, characteristics_count;
    char uuid_str[MAX_LEN_UUID_STR + 1];
    int ret, i;

    pthread_mutex_lock(&bleMtx);

    printf("------------START %s ---------------\n", addr);

    gatt_connection = gattlib_connect(nullptr, addr, BDADDR_LE_PUBLIC, BT_SEC_LOW, 0, 0);
    if (gatt_connection == nullptr) {
        gatt_connection = gattlib_connect(nullptr, addr, BDADDR_LE_RANDOM, BT_SEC_LOW, 0, 0);
        if (gatt_connection == nullptr) {
            fprintf(stderr, "Fail to connect to the bluetooth device.\n");
            goto connection_exit;
        } else {
            puts("Succeeded to connect to the bluetooth device with random address.");
        }
    } else {
        puts("Succeeded to connect to the bluetooth device.");
    }

    ret = gattlib_discover_primary(gatt_connection, &services, &services_count);
    if (ret != 0) {
        fprintf(stderr, "Fail to discover primary services.\n");
        goto disconnect_exit;
    }

    for (i = 0; i < services_count; i++) {
        gattlib_uuid_to_string(&services[i].uuid, uuid_str, sizeof(uuid_str));

        printf("service[%d] start_handle:%02x end_handle:%02x uuid:%s\n", i,
               services[i].attr_handle_start, services[i].attr_handle_end,
               uuid_str);
    }
    free(services);

    ret = gattlib_discover_char(gatt_connection, &characteristics, &characteristics_count);
    if (ret != 0) {
        fprintf(stderr, "Fail to discover characteristics.\n");
        goto disconnect_exit;
    }
    for (i = 0; i < characteristics_count; i++) {
        gattlib_uuid_to_string(&characteristics[i].uuid, uuid_str, sizeof(uuid_str));

        printf("characteristic[%d] properties:%02x value_handle:%04x uuid:%s\n", i,
               characteristics[i].properties, characteristics[i].value_handle,
               uuid_str);
    }
    free(characteristics);

    disconnect_exit:
    gattlib_disconnect(gatt_connection);

    connection_exit:
    printf("------------DONE %s ---------------\n", addr);
    pthread_mutex_unlock(&bleMtx);
    return nullptr;
}

void Bluetooth::bleDiscoveredDevice(const char* addr, const char* name) {
    struct connection_t *connection;
    int ret;

    if (name) {
        printf("Discovered %s - '%s'\n", addr, name);
    } else {
        printf("Discovered %s\n", addr);
    }

    connection = (connection_t*) malloc(sizeof(struct connection_t));
    if (connection == nullptr) {
        fprintf(stderr, "Failt to allocate connection.\n");
        return;
    }
    connection->addr = strdup(addr);

    ret = pthread_create(&connection->thread, nullptr,	bleConnectDevice, connection);
    if (ret != 0) {
        fprintf(stderr, "Failt to create BLE connection thread.\n");
        free(connection);
        return;
    }
    LIST_INSERT_HEAD(&bleConnections, connection, entries);
}

std::vector<BluetoothLEDevice*> Bluetooth::scanLE() {
    std::cout << "scanning bluetooth le" << std::endl;
    std::vector<BluetoothLEDevice*> devices;
    int ret = gattlib_adapter_open(bluetoothConfiguration.interface.c_str(), &gattAdapter);
    if (ret) {
        std::cout << "could not open '" << bluetoothConfiguration.interface << std::endl;
        return devices;
    }

    pthread_mutex_lock(&bleMtx);
    ret = gattlib_adapter_scan_enable(gattAdapter, bleDiscoveredDevice, BLE_SCAN_TIMEOUT);
    if (ret) {
        std::cout << "failed to scan" << std::endl;
        return devices;
    }
    gattlib_adapter_scan_disable(gattAdapter);
    pthread_mutex_unlock(&bleMtx);

    while (bleConnections.lh_first != nullptr) {
        struct connection_t* connection = bleConnections.lh_first;
        pthread_join(connection->thread, nullptr);
        LIST_REMOVE(bleConnections.lh_first, entries);
        free(connection->addr);
        free(connection);
    }

    gattlib_adapter_close(gattAdapter);
    return devices;
}

void Bluetooth::stop() {
    setDoRun(false);
    gattlib_adapter_scan_disable(gattAdapter);
    pthread_mutex_unlock(&bleMtx);
    gattlib_adapter_close(gattAdapter);
}

void Bluetooth::run() {
    while(this->getDoRun()){
        if(!bluetoothConfiguration.onlyLE || bluetoothConfiguration.onlyClassic) {
            std::vector<BluetoothDevice*> cDevices = scanClassic();
            std::cout << "found " << cDevices.size() << " classic devices" << std::endl;
        }
        if(!bluetoothConfiguration.onlyClassic || bluetoothConfiguration.onlyLE) {
            std::vector<BluetoothLEDevice*> lDevices = scanLE();  // todo retry on disconnected / errorous devices
            std::cout << "found " << lDevices.size() << " le devices" << std::endl;
        }
    }
}