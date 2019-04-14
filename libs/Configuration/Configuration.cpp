//
// Created by insane on 17.01.19.
//

#include <iostream>
#include "Configuration.h"

Configuration::Configuration() {}

void Configuration::help() {
    std::cout << "usage: ./pwnpi {arguments}" << std::endl;
    std::cout << "\t-h\t--help" << std::endl;
    std::cout << "\t-v\t--verbose" << std::endl;
    std::cout << "\t-b/-w\t--bluetooth/--wifi" << std::endl;
    std::cout << "\t\t-i\t--interface" << std::endl;
    std::cout << "\t\t-e\t--enable" << std::endl;
    std::cout << "\t\t\t--disable" << std::endl;
    std::cout << "[wifi specific]" << std::endl;
    std::cout << "\t\t-p\t--promiscous" << std::endl;
    std::cout << "[bluetooth specific]" << std::endl;
    std::cout << "\t\t-ole\t--only-le" << std::endl;
    std::cout << "\t\t-oc\t--only-classic" << std::endl;
    std::cout << "[lipo]" << std::endl;
    std::cout << "\t-l\t--lipo" << std::endl;
    exit(0);
}

bool Configuration::in_array(std::string key, std::vector<std::string> array) {
    for(const std::string &k : array) if(key == k) return true;
    return false;
}

Configuration* Configuration::parse_arguments(int argc, char **argv) {
    auto cfg = new Configuration();
    for(int i=0; i<argc; i++){
        std::string a = std::string(argv[i]);
        if(in_array(a, {"-h", "--help"})) help();
        if(in_array(a, {"-d", "--debug"})) cfg->systemConfiguration.debug = true;
        if(in_array(a, {"-v", "--verbose"})) cfg->systemConfiguration.verbose = true;
        if(in_array(a, {"-w", "-b", "--wifi", "--bluetooth"})){
            std::string _a(argv[i + 1]);
            if(in_array(_a, {"-i", "--interface"})){
                std::string __a(argv[i + 2]);
                if(in_array(a, {"-b", "--bluetooth"})) cfg->bluetoothConfiguration.interface = __a;
                if(in_array(a, {"-w", "--wifi"})) cfg->wifiConfiguration.interface = __a;
            }
            if(in_array(_a, {"-e", "--enable"})){
                if(in_array(a, {"-b", "--bluetooth"})) cfg->bluetoothConfiguration.enable = true;
                if(in_array(a, {"-w", "--wifi"})) cfg->wifiConfiguration.enable = true;
            }
            if(in_array(_a, {"--disable"})){
                if(in_array(a, {"-b", "--bluetooth"})) cfg->bluetoothConfiguration.enable = false;
                if(in_array(a, {"-w", "--wifi"})) cfg->wifiConfiguration.enable = false;
            }
            if(in_array(_a, {"-p", "--promiscuous"})) cfg->wifiConfiguration.promiscuous = true;
            if(in_array(_a, {"-ole", "--only-le"})) cfg->bluetoothConfiguration.onlyLE = true;
            if(in_array(_a, {"-oc", "--only-classic"})) cfg->bluetoothConfiguration.onlyClassic = true;
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