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
    gc::GPSConfiguration gpsConfiguration;
    Position* currentPosition;

public:
    GPS();
    explicit GPS(gc::GPSConfiguration cfg);

    void run() override ;

    void setCurrentPosition(gps_data_t* data);
    void setCurrentPosition(Position* position);
    Position* getCurrentPosition();
};


#endif //PWNPI_GPS_H
