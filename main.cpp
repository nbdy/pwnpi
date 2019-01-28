#include <iostream>
#include <csignal>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include "libs/Configuration/Configuration.h"
#include "libs/Manager/Manager.h"

Manager* mgr;

/*
 * todo
 *
 *
 */

void sigHandler(int sigNum){
    BOOST_LOG_TRIVIAL(debug) << "caught signal: " << sigNum;
    mgr->setDoRun(false);
    //exit(0);
}

void atDeath(){
    BOOST_LOG_TRIVIAL(debug) << "farewell";
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
        BOOST_LOG_TRIVIAL(error) << "please run with root";
        exit(0);
    }
}

void waitForDebugger(){
    BOOST_LOG_TRIVIAL(debug) << "waiting for debugger to attach";
    bool waitForDebugger = true;
    while(waitForDebugger) sleep(2);
}

void setupLogging(bool verbose, bool debug){
    namespace keywords = boost::log::keywords;
    namespace logging = boost::log; // inb4 not healthy
    logging::add_file_log(keywords::file_name = "pwnpi.log", keywords::format = "{%Timestamp%} - {%ThreadID%} - {%Severity%} > %Message%");
    if(debug) logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::debug);
    else if(verbose) logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
    else logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::warning);
    logging::add_common_attributes();
}

int main(int argc, char** argv) {
    checkIsRoot();
    std::atexit(atDeath);
    registerSigHandlers();
    Configuration* cfg = Configuration::parse_arguments(argc, argv);
    setupLogging(cfg->getVerbose(), cfg->getDebug());
    BOOST_LOG_TRIVIAL(debug) << "initializing manager";
    mgr = new Manager(cfg);
    if(cfg->getDebug()) waitForDebugger();
    BOOST_LOG_TRIVIAL(debug) << "running manager";
    mgr->run();
    BOOST_LOG_TRIVIAL(debug) << "everything comes to an end";
    return 0;
}