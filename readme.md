### pwnpi

#### dependencies
- libgps-dev
- libtins-dev
- libboost-log-dev (git version is currently v4.1 / ubuntu18 apt is v3.4)
- libbluetooth-dev

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
[wifi specific]
		-p	--promiscous
	-l      --lipo

ex:
    sudo ./pwnpi -b -i hci1 -w -i wlan1mon -w -p
                /\          /\          /\
sets bluetooth interface    || sets wifi promiscuous
                sets wifi interface
                
==  sudo ./pwnpi --bluetooth --interface hci1 --wifi --interface wlan1mon --wifi --promiscuous 
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
A: if you want to debug something, run with gdb and set 'waitForDebugger' = false<br>