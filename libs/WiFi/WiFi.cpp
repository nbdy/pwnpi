//
// Created by insane on 17.01.19.
//

#include <iostream>
#include <boost/log/trivial.hpp>
#include "WiFi.h"

WiFi::WiFi() {
    this->cfg = new WiFiConfiguration();
    this->setGPS(new GPS());
    this->setDoRun(true);
}

WiFi::WiFi(WiFiConfiguration* cfg) {
    this->cfg = cfg;
    this->setGPS(new GPS());
    this->setDoRun(true);
}

WiFi::WiFi(WiFiConfiguration *cfg, GPS *gps) {
    this->cfg = cfg;
    this->setGPS(gps);
    this->setDoRun(true);
}

void WiFi::processDot11Frame(const Tins::Dot11 &dot11) {
    if(dot11.find_pdu<Tins::Dot11Beacon>()){
        const auto& beacon = dot11.rfind_pdu<Tins::Dot11Beacon>();
        print("beacon:");
        print("\taddr1: " + beacon.addr1().to_string());
        print("\taddr2: " + beacon.addr2().to_string());
        print("\taddr3: " + beacon.addr3().to_string());
        print("\taddr4: " + beacon.addr4().to_string());
    }
    if(dot11.find_pdu<Tins::Dot11ProbeRequest>()){
        const auto& probeReq = dot11.rfind_pdu<Tins::Dot11ProbeRequest>();
        print("probeRequest:");
        print("\taddr1: " + probeReq.addr1().to_string());
        print("\taddr2: " + probeReq.addr2().to_string());
        print("\taddr3: " + probeReq.addr3().to_string());
        print("\taddr4: " + probeReq.addr4().to_string());
    }
}

void WiFi::run() {
    print("initializing sniffer configuration");
    Tins::SnifferConfiguration cfg;
    print("setting sniffer configuration promisc mode");
    cfg.set_promisc_mode(this->cfg->getPromiscuous());
    print("initializing sniffer");
    Tins::Sniffer s(this->cfg->getInterface(), cfg);
    print(2, "running sniff_loop");
    for(const auto& pkt : s){
        if(pkt.pdu()->find_pdu<Tins::Dot11>()){
            processDot11Frame(pkt.pdu()->rfind_pdu<Tins::Dot11>());
        }
        if(!getDoRun()) break;
    }
}

