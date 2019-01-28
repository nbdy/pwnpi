//
// Created by insane on 24.01.19.
//

#ifndef PWNPI_PACKET_H
#define PWNPI_PACKET_H


#include "../Device/Device.h"

class Packet {
private:
    Device* sender;
    Device* receiver;

public:
    Packet();
    Packet(Tins::Packet &pkt);

    Device* getSender();
    Device* getReceiver();

};


#endif //PWNPI_PACKET_H
