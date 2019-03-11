//
// Created by insane on 17.01.19.
//

#ifndef PWNPI_WIFI_H
#define PWNPI_WIFI_H

#include <tins/tins.h>
#include "../Configuration/Configuration.h"
#include "../GPS/GPS.h"
#include "../Runnable/Runnable.h"

class WiFi : public RunnableWithGPS {
private:
    std::string name = "WiFi";
    wc::WifiConfiguration wifiConfiguration;
    void processDot11Frame(const Tins::Dot11& dot11);

public:
    explicit WiFi(wc::WifiConfiguration cfg);
    WiFi(wc::WifiConfiguration cfg, GPS* gps);
    void run() override;
};


#endif //PWNPI_WIFI_H
