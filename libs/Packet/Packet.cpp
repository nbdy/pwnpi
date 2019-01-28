//
// Created by insane on 24.01.19.
//

#include "Packet.h"

Packet::Packet() {
    receiver = new Device();
    sender = new Device();
}

Packet::Packet(Tins::Packet &pkt) {
    // Tins::Dot11 d = pkt.
    receiver = new Device();
    sender = new Device();
}

Device* Packet::getReceiver() {
    return this->receiver;
}

Device* Packet::getSender() {
    return this->sender;
}