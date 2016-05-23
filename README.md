# PiMatrix

PiMatrix is a project in which we combine the concepts of distributed computing
with external IO by use of Raspberry Pis, a messaging library called ZeroMQ and
wiringPi.

This combines to be a system where input is given by remote input publishers and
a single subscriber by the use of a Message Broker.

Inside the eagle folder, there is a design for an add-on board suited for a Raspberry Pi 2+.
This add-on board includes 2 8x8 LED matrices to form a complete 16x8 LED matrix display.

The setup consists of the following systems:
* Laptop running Avahi, DNSMasq (lightweight DHCP), MessageBroker, JoystickPublisher
* Raspberry Pi 2 with add-on board (henceforth called ScreenPi), running Avahi, MatrixSnake
* Raspberry PI 2 with mouse (henceforth called MousePi), running Avahi, MousePublisher
