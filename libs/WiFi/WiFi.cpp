//
// Created by insane on 17.01.19.
//

#include <iostream>
#include <boost/log/trivial.hpp>
#include "WiFi.h"

WiFi::WiFi(wc::WifiConfiguration cfg) {
    wifiConfiguration = std::move(cfg);
    this->setGPS(new GPS());
    this->setDoRun(!this->wifiConfiguration.interface.empty());
}

WiFi::WiFi(wc::WifiConfiguration cfg, GPS *gps) {
    wifiConfiguration = std::move(cfg);
    this->setGPS(gps);
    this->setDoRun(!this->wifiConfiguration.interface.empty());
}

void WiFi::processDot11Frame(const Tins::Dot11 &dot11) {
    if(dot11.find_pdu<Tins::Dot11Beacon>()){
        const auto& beacon = dot11.rfind_pdu<Tins::Dot11Beacon>();
        std::cout << "beacon:" << std::endl;
        std::cout << "\taddr1: " << beacon.addr1().to_string() << std::endl;
        std::cout << "\taddr2: " << beacon.addr2().to_string() << std::endl;
        std::cout << "\taddr3: " << beacon.addr3().to_string() << std::endl;
        std::cout << "\taddr4: " << beacon.addr4().to_string() << std::endl;
    }
    if(dot11.find_pdu<Tins::Dot11ProbeRequest>()){
        const auto& probeReq = dot11.rfind_pdu<Tins::Dot11ProbeRequest>();
        std::cout << "probeRequest:" << std::endl;
        std::cout << "\taddr1: " + probeReq.addr1().to_string() << std::endl;
        std::cout << "\taddr2: " + probeReq.addr2().to_string() << std::endl;
        std::cout << "\taddr3: " + probeReq.addr3().to_string() << std::endl;
        std::cout << "\taddr4: " + probeReq.addr4().to_string() << std::endl;
    }
}

void WiFi::run() {
    if(getDoRun()){
        std::cout << "initializing sniffer configuration" << std::endl;
        Tins::SnifferConfiguration cfg;
        std::cout << "setting sniffer configuration promisc mode" << std::endl;
        cfg.set_promisc_mode(wifiConfiguration.promiscuous);
        std::cout << "initializing sniffer" << std::endl;
        Tins::Sniffer s(wifiConfiguration.interface, cfg);
        std::cout << "running sniff_loop" << std::endl;
        for(const auto& pkt : s){
            if(pkt.pdu()->find_pdu<Tins::Dot11>()){
                processDot11Frame(pkt.pdu()->rfind_pdu<Tins::Dot11>());
            }
            if(!getDoRun()) break;
        }
    } else {
        std::cout << "wifi wasn't supposed to run" << std::endl;
    }
}

