#!/bin/bash

if [[ ! $(id -u) -ne 0 ]] ; then echo "we'll request root as we go" ; exit 1 ; fi

echo "installing libgps, libbluetooth, libpcap, libssl, libev-dev  and cmake"

sudo apt install libgps-dev libbluetooth-dev libboost-regex libpcap-dev libssl-dev libev-dev cmake -y

echo "getting and installing submodules"
git submodule update --init


echo "installing libtins"
cd /tmp/
git clone https://github.com/mfontanini/libtins
cd libtins
mkdir build
cd build
cmake ../ -DLIBTINS_ENABLE_CXX11=1
make -j4
make install
cd /tmp/
rm -rf libtins/

echo "done"