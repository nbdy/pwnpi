//
// Created by insane on 20.01.19.
//

#include "Device.h"

Device::Device() {
    address = "FF:FF:FF:FF:FF:FF";
    receiver = "FF:FF:FF:FF:FF:FF";

}

Device::Device(Tins::Dot11 dot11, bool src) {
    // according to https://dalewifisec.wordpress.com/2014/05/17/the-to-ds-and-from-ds-fields/
    if(dot11.from_ds() == 0 && dot11.to_ds() == 0){
        // adhoc / not leaving network
        // addr1 dst
        // addr2 src
        // addr3 bssid

    } else if (dot11.from_ds() == 0 && dot11.to_ds() == 1){
        // addr1 bssid
        // addr2 src
        // addr3 dst

    } else if(dot11.to_ds() == 0 && dot11.from_ds() == 1){
        // entering network / to device in network
        // addr1 dst
        // addr2 bssid
        // addr3 src
    } else if(dot11.to_ds() == 1 && dot11.from_ds() == 1){
        // in wds
        // addr1 rx
        // addr2 tx
        // addr3 dst
        // addr4 src
    }
}