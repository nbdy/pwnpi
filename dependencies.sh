#!/bin/bash

if [[ ! $(id -u) -ne 0 ]] ; then echo "we'll request root as we go" ; exit 1 ; fi

echo "installing development libraries:"
echo "gps, bluetooth, readline, boost-regex, ev, pcap, ssl"
echo "aswell as cmake and bluez"

sudo apt-get install -y libgps-dev libbluetooth-dev libboost-regex-dev libpcap-dev libssl-dev \
                        libev-dev cmake bluez libreadline-dev > /dev/null


if [ "$(whereis libsqlite3)" == "libsqlite3:" ]; then
  echo "installing libsqlite3"
  cd /tmp/ || exit
  wget https://sqlite.org/2020/sqlite-autoconf-3310100.tar.gz
  tar xf sqlite-autoconf-3310100.tar.gz
  rm sqlite-autoconf-3310100.tar.gz
  cd sqlite-autoconf-3310100 || exit
  ./configure
  make -j4
  sudo make install
  cd /tmp/ || exit
  rm -rf sqlite-autoconf-3310100
else
  echo "libsqlite3 is already installed"
fi

echo "getting and installing submodules"
git submodule update --init

if [ "$(whereis libtins)" == "libtins:" ]; then
  echo "installing libtins"
  cd /tmp/ || exit
  git clone https://github.com/mfontanini/libtins
  cd libtins || exit
  mkdir build
  cd build || exit
  cmake ../ -DLIBTINS_ENABLE_CXX11=1
  make -j4
  sudo make install
  cd /tmp/ || exit
  rm -rf libtins/
else
  echo "libtins is already installed"
fi

if [ "$(whereis libtinyb)" == "libtinyb:" ]; then
  echo "installing libtinyb"
  cd /tmp/ || exit
  git clone https://github.com/intel-iot-devkit/tinyb
  cd tinyb || exit
  mkdir build
  cd build || exit
  cmake ..
  make -j4
  sudo make install
  cd /tmp/ || exit
  rm -rf tinyb
else
  echo "libtinyb is already installed"
fi

# shellcheck disable=SC2188
<<COMMENT
if [ "$(whereis gattlib)" == "libgattlib:" ]; then
  echo "installing gattlib"
  git clone https://github.com/labapart/gattlib
  cd gattlib || exit
  mkdir build
  cd build || exit
  cmake .. -DGATTLIB_BUILD_DOCS=NO
  make -j4
  sudo make install
  cd /tmp/ || exit
  rm -rf gattlib
else
  echo "gattlib is already instlled"
fi
COMMENT

echo "done"