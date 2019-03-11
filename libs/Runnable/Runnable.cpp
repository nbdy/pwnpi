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

void Runnable::print(std::string data) {
    print(1, data);  // defaults to debug
}

void Runnable::print(uint8_t sev, std::string data) {
    mtx.lock();
    BOOST_LOG_TRIVIAL(debug) << "{" << name << "} : " << data;
    mtx.unlock();
}

bool Runnable::getDoRun() {
    return doRun;
}

void Runnable::setDoRun(bool doRun) {
    print(2, "setting doRun to " + std::string(doRun ? "true" : "false"));
    this->doRun = doRun;
}

std::thread Runnable::getThread() {
    print("manufacturing and returning thread");
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