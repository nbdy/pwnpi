//
// Created by insane on 17.01.19.
//

#include <iostream>
#include <boost/log/trivial.hpp>
#include "Manager.h"

Manager::Manager(Configuration* cfg) {
    this->cfg = cfg;
    std::cout << "initializing gps" << std::endl;
    gps = new GPS(cfg->getGPSConfiguration());
    std::cout << "initializing wifi" << std::endl;
    wifi = new WiFi(cfg->getWifiConfiguration(), gps);
    std::cout << "initializing bluetooth" << std::endl;
    bt = new Bluetooth(cfg->getBluetoothConfiguration(), gps);
    setDoRun(true);
}

void Manager::run() {
    std::cout << "getting gps thread" << std::endl;
    std::thread gpsThread = gps->getThread();
    std::cout << "getting wifi thread" << std::endl;
    std::thread wifiThread = wifi->getThread();
    std::cout << "getting bluetooth thread" << std::endl;
    std::thread btThread = bt->getThread();
    std::cout << "running in a loop" << std::endl;

    while (doRun){
        // todo collect results
        sleep(2); // idk
    }

    std::cout << "loop is done running; telling children to stop" << std::endl;
    wifi->stop();
    bt->stop();
    gps->stop();

    wifiThread.join();
    btThread.join();
    gpsThread.join();

    std::cout << "everything should be quiet" << std::endl;
}

bool Manager::getDoRun() {
    return doRun;
}

void Manager::setDoRun(bool doRun) {
    std::cout << "setting doRun to " << doRun << std::endl;
    this->doRun = doRun;
}

Bluetooth* Manager::getBluetooth() {
    return bt;
}

void Manager::setBluetooth(Bluetooth *bluetooth) {
    this->bt = bluetooth;
}

WiFi* Manager::getWiFi() {
    return wifi;
}

void Manager::setWiFi(WiFi *wiFi) {
    this->wifi = wiFi;
}

Configuration* Manager::getConfiguration() {
    return cfg;
}

void Manager::setConfiguration(Configuration *cfg) {
    this->cfg = cfg;
}

GPS* Manager::getGPS() {
    return gps;
}

void Manager::setGPS(GPS *gps) {
    this->gps = gps;
}