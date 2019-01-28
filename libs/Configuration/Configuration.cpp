//
// Created by insane on 17.01.19.
//

#include <iostream>
#include <boost/log/trivial.hpp>
#include "Configuration.h"

void Configuration::help() {
    BOOST_LOG_TRIVIAL(info) << "usage: ./pwnpi {arguments}";
    BOOST_LOG_TRIVIAL(info) << "\t-h\t--help";
    BOOST_LOG_TRIVIAL(info) << "\t-v\t--verbose";
    BOOST_LOG_TRIVIAL(info) << "\t-b/-w\t--bluetooth/--wifi";
    BOOST_LOG_TRIVIAL(info) << "\t\t-i\t--interface";
    BOOST_LOG_TRIVIAL(info) << "[wifi specific]";
    BOOST_LOG_TRIVIAL(info) << "\t\t-p\t--promiscous";
    BOOST_LOG_TRIVIAL(info) << "\t-l\t--lipo";
    exit(0);
}

std::string WirelessConfiguration::getInterface() {
    return interface;
}

void WirelessConfiguration::setInterface(std::string interface) {
    BOOST_LOG_TRIVIAL(debug) << "setting interface: " << interface;
    this->interface = std::move(interface);
}

BluetoothConfiguration::BluetoothConfiguration() {
    this->setInterface("hci0");
}


WiFiConfiguration::WiFiConfiguration() {
    this->setInterface("wlan0");
    this->promiscuous = true;
}

bool WiFiConfiguration::getPromiscuous() {
    return promiscuous;
}

void WiFiConfiguration::setPromiscuous(bool promiscuous) {
    BOOST_LOG_TRIVIAL(debug) << "setting wifi mode promiscuous: " << promiscuous;
    this->promiscuous = promiscuous;
}

Configuration::Configuration() {
    this->bluetoothConfiguration = new BluetoothConfiguration();
    this->wiFiConfiguration = new WiFiConfiguration();
}


bool Configuration::in_array(std::string key, std::vector<std::string> array) {
    for(const std::string &k : array) if(key == k) return true;
    return false;
}


Configuration* Configuration::parse_arguments(int argc, char **argv) {
    BOOST_LOG_TRIVIAL(debug) << "parsing arguments";
    auto cfg = new Configuration();
    for(int i=0; i<argc; i++){
        std::string a = std::string(argv[i]);
        if(in_array(a, {"-h", "--help"})) help();
        if(in_array(a, {"-d", "--debug"})) cfg->debug = true;
        if(in_array(a, {"-v", "--verbose"})) cfg->verbose = true;
        if(in_array(a, {"-w", "-b", "--wifi", "--bluetooth"})){
            std::string _a(argv[i + 1]);
            if(in_array(_a, {"-i", "--interface"})){
                std::string __a(argv[i + 2]);
                if(in_array(a, {"-b", "--blueooth"})) cfg->bluetoothConfiguration->setInterface(__a);
                if(in_array(a, {"-w", "--wifi"})) cfg->wiFiConfiguration->setInterface(__a);
            }
            if(in_array(_a, {"-p", "--promiscuous"})) cfg->wiFiConfiguration->setPromiscuous(true);
        }
    }

    if(geteuid() != 0) cfg->wiFiConfiguration->setPromiscuous(false);

    return cfg;
}

BluetoothConfiguration* Configuration::getBluetoothConfiguration() {
    return bluetoothConfiguration;
}

void Configuration::setBluetoothConfiguration(BluetoothConfiguration *cfg) {
    this->bluetoothConfiguration = cfg;
}

WiFiConfiguration* Configuration::getWifiConfiguration() {
    return wiFiConfiguration;
}

void Configuration::setWiFiConfiguration(WiFiConfiguration *cfg) {
    this->wiFiConfiguration = cfg;
}

GPSConfiguration* Configuration::getGPSConfiguration() {
    return gpsConfiguration;
}

void Configuration::setGPSConfiguration(GPSConfiguration *cfg) {
    gpsConfiguration = cfg;
}

GPSConfiguration::GPSConfiguration() {

}

bool Configuration::getDebug() {
    return debug;
}

void Configuration::setDebug(bool debug) {
    this->debug = debug;
}

void Configuration::setVerbose(bool verbose) {
    this->verbose = verbose;
}

bool Configuration::getVerbose() {
    return verbose;
}

bool Configuration::getLipo() {
    return lipo;
}

void Configuration::setLipo(bool lipo) {
    this->lipo = lipo;
}