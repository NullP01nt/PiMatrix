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
* Laptop [Avahi-daemon, DNSMasq] (broker.local)
* Raspberry Pi 2 with add-on board [Avahi-daemon] (screenpi.local)
* Raspberry PI 2 with mouse [Avahi-daemon] (mousepi.local)
