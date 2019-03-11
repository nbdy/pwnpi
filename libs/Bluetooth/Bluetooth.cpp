//
// Created by insane on 17.01.19.
//

#include <iostream>
#include <boost/log/trivial.hpp>
#include "Bluetooth.h"


Bluetooth::Bluetooth(bc::BluetoothConfiguration cfg) {
    bluetoothConfiguration = std::move(cfg);
    this->setGPS(new GPS());
    setDoRun(true);
}

Bluetooth::Bluetooth(bc::BluetoothConfiguration cfg, GPS *gps) {
    bluetoothConfiguration = std::move(cfg);
    this->setGPS(gps);
    setDoRun(true);
}

void Bluetooth::run() {
    print("running bluetooth");
    inquiry_info* ii = nullptr;
    int maxRsp, numRsp, devId, sck, len, flags, i;
    char addr[19] = {0};
    char name[248] = {0};
    print("getting hci route");
    devId = hci_get_route(nullptr);
    print("opening hci device");
    sck = hci_open_dev(devId);
    print("checking if devId or sck is -X");
    if(devId < 0 || sck < 0) this->setDoRun(false); // idk
    print(2, "running bluetooth loop");
    while(this->getDoRun()){
        len = 8;
        maxRsp = 255;
        flags = IREQ_CACHE_FLUSH;
        ii = (inquiry_info*) malloc(maxRsp * sizeof(inquiry_info));
        print("inquiring bluetooth devices");
        numRsp = hci_inquiry(devId, len, maxRsp, nullptr, &ii, flags);

        for (i = 0; i < numRsp; i++) {
            ba2str(&(ii+i)->bdaddr, addr);
            memset(name, 0, sizeof(name));
            if (hci_read_remote_name(sck, &(ii+i)->bdaddr, sizeof(name),
                                     name, 0) < 0)
                strcpy(name, "[unknown]");
            print(std::string("found device '") + name + std::string("' with address '") + std::string(addr) + "'");
        }
        usleep(500); // idk
    }
    print("bluetooth loop has finished running; cleaning up");
    free( ii );
    close(sck);
}