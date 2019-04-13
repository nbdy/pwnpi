//
// Created by insane on 18.01.19.
//

#include <iostream>
#include <boost/log/trivial.hpp>
#include "GPS.h"


GPS::GPS() {
    this->currentPosition = new Position();
    setDoRun(true);
}

GPS::GPS(gc::GPSConfiguration cfg) {
    this->gpsConfiguration = cfg;
    setDoRun(true);
}

void GPS::run() {
    gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);
    if(gps_rec.stream(WATCH_ENABLE|WATCH_JSON) == nullptr) this->setDoRun(false);
    while (this->getDoRun()) {
        struct gps_data_t* nd;
        if(!gps_rec.waiting(50000000)) continue;
        if((nd = gps_rec.read()) == nullptr) this->setDoRun(false);
        else setCurrentPosition(nd);
    }
}

Position* GPS::getCurrentPosition() {
    return currentPosition;
}

void GPS::setCurrentPosition(Position* position) {
    this->currentPosition = position;
}

void GPS::setCurrentPosition(gps_data_t *data) {
    this->currentPosition = new Position(data);
}

Position::Position() {
    this->longitude = 0;
    this->latitude = 0;
    this->altitude = 0;
    this->speed = 0;
    this->satellitesUsed = 0;
}

Position::Position(gps_data_t *data) {
    this->longitude = data->fix.longitude;
    this->latitude = data->fix.latitude;
    this->altitude = data->fix.altitude;
    this->speed = data->fix.speed;
    this->satellitesUsed = data->satellites_used;
}

double Position::getLongitude() {
    return longitude;
}

void Position::setLongitude(double longitude) {
    this->longitude = longitude;
}

double Position::getLatitude() {
    this->latitude;
}

void Position::setLatitude(double latitude) {
    this->latitude = latitude;
}

double Position::getAltitude() {
    return this->altitude;
}

void Position::setAltitude(double altitude) {
    this->altitude = altitude;
}

double Position::getSpeed() {
    return this->speed;
}

void Position::setSpeed(double speed) {
    this->speed = speed;
}

int Position::getSatellitesUsed() {
    return satellitesUsed;
}

void Position::setSatellitesUsed(int satellitesUsed) {
    this->satellitesUsed = satellitesUsed;
}