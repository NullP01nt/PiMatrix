# PiMatrix

PiMatrix is a project in which we combine the concepts of distributed computing
with external IO by use of Raspberry Pis, a messaging library called ZeroMQ and
wiringPi.

This combines to be a system where input is given by remote input publishers and
a single subscriber by the use of a Message Broker.

Inside the eagle folder, there is a design for an add-on board suited for a Raspberry Pi 2+.
This add-on board includes 2 8x8 LED matrices to form a complete 16x8 LED matrix display.

The software side of things is managed by the following services:
* Avahi-daemon (mDNS)
* DNSMasq (DHCP)

Our setup consists of the following systems:
The setup consists of the following systems:
* Laptop 
  * Avahi-daemon (broker.local)
  * DNSMasq 
* Raspberry Pi 2 with add-on board 
  * Avahi-daemon (screenpi.local)
* Raspberry PI 2 with mouse 
  * Avahi-daemon (mousepi.local)

#### Setup guide for the project ####

#### On the laptop ####
```bash
su
apt-add-repository ppa:segf4ult/zeromq
apt update
apt install build-essential git-core qttools5-dev libqt5core5a avahi-daemon pkg-config cppzmq
exit
git clone https://github.com/NullP01nt/PiMatrix.git
cd PiMatrix/src/MessageBroker
qmake
make
./MessageBroker &
```
##### If a PS3 controller is desired, connect it to the laptop
[check out setup guide] (https://help.ubuntu.com/community/Sixaxis)
```bash
echo "
[publisher]
host=broker.local
topic=CTRL
port=55554
" > ~/.config/SDU-EMB4/P3_JOYPUB.conf
cd -
cd PiMatrix/src/JoystickPublisher
qmake
make
./JoystickPublisher &
```
#### on the pi's ####
```bash
sudo su
apt-add-repository ppa:segf4ult/zeromq
apt update
apt install build-essential git-core qttools5-dev libqt5core5a avahi-daemon pkg-config cppzmq
exit
git clone git://git.drogon.net/wiringPi
cd wiringPi
./build
cd -
git clone https://github.com/NullP01nt/PiMatrix.git
cd PiMatrix
```
##### On the MousePi #####
```bash
cd src/MousePublisher
qmake
make
##### plug in mouse #####
MOUSE=/dev/input/$(ls -lc /dev/input/by-path/ | grep event-mouse | head -n 1 | rev | cut -d '/' -f 1 | rev )
sudo chmod +r $MOUSE
echo "
[device]
mouse=$MOUSE
[publisher]
host=broker.local
topic=CTRL
port=55554
" > ~/.config/SDU-EMB4/P3_MOUSEPUB.conf
echo "PATH=\$PATH:$pwd" >> ~/.bashrc
source ~/.bashrc
MousePublisher
```
##### On the ScreenPi #####
```bash
cd src/MatrixSnake
qmake
make
echo "
[subscriber]
host=broker.local
topic=CTRL
port=55555
" > ~/.config/SDU-EMB4/P3_MATSNAKE.conf
echo "PATH=\$PATH:$pwd" >> ~/.bashrc
source ~/.bashrc
MatrixSnake
```
