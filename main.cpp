#include <iostream>
#include <csignal>
#include "libs/Configuration/Configuration.h"
#include "libs/Manager/Manager.h"

Manager* mgr;

/*
 * todo
 *
 *
 */

void sigHandler(int sigNum){
    std::cout << "caught signal: " << sigNum << std::endl;
    mgr->setDoRun(false);
    //exit(0);
}

void atDeath(){
    std::cout << "farewell" << std::endl;
    //exit(0);
}

void registerSigHandlers(){
    signal(SIGTERM, sigHandler);
    signal(SIGINT, sigHandler);
    signal(SIGKILL, sigHandler);
    signal(SIGHUP, sigHandler);
}

void checkIsRoot(){
    if(geteuid() != 0){
        std::cout << "please run with root" << std::endl;
        exit(0);
    }
}

void waitForDebugger(){
    std::cout << "waiting for debugger to attach" << std::endl;
    bool waitForDebugger = true;
    while(waitForDebugger) sleep(2);
}

int main(int argc, char** argv) {
    checkIsRoot();
    std::atexit(atDeath);
    registerSigHandlers();
    Configuration* cfg = Configuration::parse_arguments(argc, argv);
    std::cout << "initializing manager" << std::endl;
    mgr = new Manager(cfg);
    if(cfg->getSystemConfiguration().debug) waitForDebugger();
    std::cout << "running manager" << std::endl;
    mgr->run();
    std::cout << "everything comes to an end" << std::endl;
    return 0;
}