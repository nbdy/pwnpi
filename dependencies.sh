#!/bin/bash

if [[ $(id -u) -ne 0 ]] ; then echo "run with sudo / root" ; exit 1 ; fi

echo "installing libgps, libbluetooth, liboost-log, libpcap, libssl, libev-dev  and cmake"

apt install libgps-dev libbluetooth-dev libboost-log-dev libpcap-dev libssl-dev libev-dev cmake -y

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

echo "installing redis"

wget http://download.redis.io/releases/redis-5.0.3.tar.gz
tar xf redis-5.0.3.tar.gz
rm redis-5.0.3.tar.gz
cd redis-5.0.3/
make -j 8
sudo make install
cd /tmp/
rm -rf redis-5.0.3/

git clone https://github.com/redis/hiredis/
cd hiredis
make
sudo make install
cd /tmp/
rm -rf hiredis/

git clone https://github.com/hmartiro/redox
cd redox
./make.sh
cd build/
make install
cd /tmp/
rm -rf redox/
