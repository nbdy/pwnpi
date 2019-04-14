//
// Created by insane on 19.01.19.
//

#include <iostream>
#include <sstream>
#include <boost/log/trivial.hpp>
#include "Runnable.h"
#include "../GPS/GPS.h"


Runnable::Runnable() {

}

void Runnable::run() {}

bool Runnable::getDoRun() {
    return doRun;
}

void Runnable::setDoRun(bool doRun) {
    this->doRun = doRun;
}

std::thread Runnable::getThread() {
    return std::thread([&] {this->run();});
}

RunnableWithGPS::RunnableWithGPS() {
    gps = new GPS();
}

RunnableWithGPS::RunnableWithGPS(gc::GPSConfiguration cfg) {
    gps = new GPS(cfg);
}

RunnableWithGPS::RunnableWithGPS(GPS* gps) {
    this->gps = gps;
}

GPS* RunnableWithGPS::getGPS() {
    return gps;
}

void RunnableWithGPS::setGPS(GPS* gps) {
    this->gps = gps;
}

std::string Runnable::getName() {
    return name;
}

void Runnable::setName(const std::string& name) {
    this->name = name;
}

void Runnable::stop() {
    setDoRun(false);
}