//
// Created by insane on 17.01.19.
//

#include <iostream>
#include <boost/log/trivial.hpp>
#include "Configuration.h"

Configuration::Configuration() {}

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
                if(in_array(a, {"-b", "--blueooth"})) cfg->bluetoothConfiguration.interface = __a;
                if(in_array(a, {"-w", "--wifi"})) cfg->wifiConfiguration.interface = __a;
            }
            if(in_array(_a, {"-p", "--promiscuous"})) cfg->wifiConfiguration.promiscuous = true;
        }
    }

    if(geteuid() != 0) cfg->wifiConfiguration.promiscuous = false;

    return cfg;
}

db::DatabaseConfiguration Configuration::getDatabaseConfiguration() {return databaseConfiguration;}

bc::BluetoothConfiguration Configuration::getBluetoothConfiguration() {return bluetoothConfiguration;}

gc::GPSConfiguration Configuration::getGPSConfiguration() {return gpsConfiguration;}

wc::WifiConfiguration Configuration::getWifiConfiguration() {return wifiConfiguration;}

sc::SystemConfiguration Configuration::getSystemConfiguration() {return systemConfiguration;}