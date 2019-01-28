//
// Created by insane on 17.01.19.
//

#ifndef PWNPI_CONFIGURATION_H
#define PWNPI_CONFIGURATION_H

#include <string>
#include <vector>


class WirelessConfiguration {
private:
    std::string interface;

public:
    void setInterface(std::string interface);
    std::string getInterface();

};


class BluetoothConfiguration : public WirelessConfiguration{
public:
    BluetoothConfiguration();
};


class WiFiConfiguration : public WirelessConfiguration {
private:
    bool promiscuous;

public:
    WiFiConfiguration();

    void setPromiscuous(bool promiscuous);
    bool getPromiscuous();
};


class GPSConfiguration {
public:
    GPSConfiguration();
};


class Configuration {
private:
    bool debug = false;
    bool verbose = false;
    bool lipo = false;

    BluetoothConfiguration* bluetoothConfiguration;
    WiFiConfiguration* wiFiConfiguration;
    GPSConfiguration* gpsConfiguration;

    static bool in_array(std::string key, std::vector<std::string> array);
    static void help();

public:
    static Configuration* parse_arguments(int argc, char** argv);

    Configuration();

    BluetoothConfiguration* getBluetoothConfiguration();
    void setBluetoothConfiguration(BluetoothConfiguration* cfg);

    WiFiConfiguration* getWifiConfiguration();
    void setWiFiConfiguration(WiFiConfiguration* cfg);

    GPSConfiguration* getGPSConfiguration();
    void setGPSConfiguration(GPSConfiguration* cfg);

    bool getDebug();
    void setDebug(bool debug);

    bool getVerbose();
    void setVerbose(bool verbose);

    bool getLipo();
    void setLipo(bool lipo);
};




#endif //PWNPI_CONFIGURATION_H
