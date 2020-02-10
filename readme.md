### pwnpi

[![asciicast](https://asciinema.org/a/299834.svg)](https://asciinema.org/a/299834)

#### dependencies
- libgps-dev
- libtins-dev
- libboost-log-dev (git version is currently v4.1 / ubuntu18 apt is v3.4)
- libbluetooth-dev
- slite3pp

```
sudo ./dependencies.sh
```

#### build

```
mkdir build; cd build; cmake ..; make
```

#### run

```
sudo ./pwnpi --help
usage: ./pwnpi {arguments}
	-h      --help
	-d      --debug
	-v      --verbose
	-b/-w	--bluetooth/--wifi
		-i	--interface
		-e  --enable
		    --disable
[wifi specific]
		-p	--promiscous
[bluetooth specific]
        -ol --only-le
        -oc --only-classic
[lipo]
	-l      --lipo

ex1:
    sudo ./pwnpi -b -i hci1 -w -i wlan1mon -w -p
                /\          /\          /\
sets bluetooth interface    || sets wifi promiscuous
                sets wifi interface
                
==  sudo ./pwnpi --bluetooth --interface hci1 --wifi --interface wlan1mon --wifi --promiscuous 

ex2:
    ./pwnpi -b --disable -w -i wlan0
               /\           /\
       disables bluetooth   sets wifi interface

ex3:
    sudo ./pwnpi -b -i hci0 -b -ol -w --disable
                /\        /\      /\
sets bluetooth interface  ||    disables wifi
    indicates that we only want to scan for bluetoot low energy devices
```

#### faq

Q: why 'pwnpi', it can run anywhere<br>
A: i just run it on a rpi zero, it has been created with only that thought in mind<br>

Q: does it leak?<br>
A: idk, valgrinded everything besides the wifi/bluetooth part and it seemed fine<br>
Q: why didn't you check the wifi/bluetooth part?<br>
A: didn't look into vgdb yet; else i'd need to run clion as root<br>
Q: why don't you wanna run clion as root?<br>
A: why don't you?<br>

Q: i ran it with -d and it's stuck at 'waiting for debugger'<br>
A: if you want to debug something, run with gdb and set 'waitingForDebugger' = false<br>

Q: ble scan throws segmentation fault<br>
A: right? and the code is basically copied from the gattlib examples<br>