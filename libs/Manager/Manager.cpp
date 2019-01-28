//
// Created by insane on 17.01.19.
//

#include <iostream>
#include <boost/log/trivial.hpp>
#include "Manager.h"

Manager::Manager(Configuration* cfg) {
    this->cfg = cfg;
    BOOST_LOG_TRIVIAL(debug) << "initializing gps";
    gps = new GPS(cfg->getGPSConfiguration());
    BOOST_LOG_TRIVIAL(debug) << "initializing wifi";
    wifi = new WiFi(cfg->getWifiConfiguration(), gps);
    BOOST_LOG_TRIVIAL(debug) << "initializing bluetooth";
    bt = new Bluetooth(cfg->getBluetoothConfiguration(), gps);
    setDoRun(true);
}

void Manager::run() {
    BOOST_LOG_TRIVIAL(debug) << "getting gps thread";
    std::thread gpsThread = gps->getThread();
    BOOST_LOG_TRIVIAL(debug) << "getting wifi thread";
    std::thread wifiThread = wifi->getThread();
    BOOST_LOG_TRIVIAL(debug) << "getting bluetooth thread";
    std::thread btThread = bt->getThread();
    BOOST_LOG_TRIVIAL(debug) << "running in a loop";

    while (doRun){

        sleep(2); // idk
    }

    BOOST_LOG_TRIVIAL(debug) << "loop is done running; telling children to stop";
    wifi->setDoRun(false);
    bt->setDoRun(false);
    gps->setDoRun(false);

    wifiThread.join();
    btThread.join();
    gpsThread.join();

    BOOST_LOG_TRIVIAL(debug) << "everything should be quiet";
}

bool Manager::getDoRun() {
    return doRun;
}

void Manager::setDoRun(bool doRun) {
    BOOST_LOG_TRIVIAL(debug) << "setting doRun to " << doRun;
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