TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

CONFIG += c++11 link_pkgconfig
PKGCONFIG += libzmq


TARGET = mouse

SOURCES += main.cpp
