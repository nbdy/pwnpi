//
// Created by insane on 18.01.19.
//

#ifndef PWNPI_GPS_H
#define PWNPI_GPS_H

#include <libgpsmm.h>
#include "../Runnable/Runnable.h"
#include "../Configuration/Configuration.h"


class Position {
    double longitude;
    double latitude;
    double altitude;
    double speed;
    int satellitesUsed;

public:
    Position();
    explicit Position(gps_data_t* data);

    double getLongitude();
    void setLongitude(double longitude);

    double getLatitude();
    void setLatitude(double latitude);

    double getAltitude();
    void setAltitude(double altitude);

    double getSpeed();
    void setSpeed(double speed);

    int getSatellitesUsed();
    void setSatellitesUsed(int satellitesUsed);

};

class GPS : public Runnable {
private:
    std::string name = "GPS";
    GPSConfiguration* cfg;
    Position* currentPosition;

public:
    GPS();
    explicit GPS(GPSConfiguration* cfg);

    void run();

    void setCurrentPosition(gps_data_t* data);
    void setCurrentPosition(Position* position);
    Position* getCurrentPosition();

    GPSConfiguration* getGPSConfiguration();
    void setGPSConfiguration(GPSConfiguration* cfg);
};


#endif //PWNPI_GPS_H
