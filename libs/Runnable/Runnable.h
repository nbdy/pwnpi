//
// Created by insane on 19.01.19.
//

#ifndef PWNPI_RUNNABLE_H
#define PWNPI_RUNNABLE_H

#include "../Configuration/Configuration.h"
#include <thread>
#include <mutex>


class Runnable {
private:
    std::string name = "Runnable";
    bool doRun;
    std::mutex mtx;

public:
    Runnable();

    virtual void run();
    virtual void stop();

    bool getDoRun();
    void setDoRun(bool doRun);

    std::string getName();
    void setName(const std::string& name);

    std::thread getThread();
};

class GPS;

class RunnableWithGPS : public Runnable {
private:
    std::string name = "RunnableWithGPS";
    GPS* gps;

public:
    RunnableWithGPS();
    explicit RunnableWithGPS(gc::GPSConfiguration cfg);
    explicit RunnableWithGPS(GPS* gps);

    void setGPS(GPS* gps);
    GPS* getGPS();
};


#endif //PWNPI_RUNNABLE_H
