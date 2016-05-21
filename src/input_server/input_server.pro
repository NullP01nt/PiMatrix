TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

include($$PWD/../Extended/common.pri)

TARGET = input_server

SOURCES += main.cpp \
    mouse_reader.cpp \
    publisher.cpp

HEADERS += \
    mouse_reader.h \
    publisher.h
