TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

include($$PWD/../common.pri)

MOC_DIR=$$PWD/build/moc
OBJECTS_DIR=$$PWD/build/objs

TARGET = input_server

SOURCES += main.cpp \
    mouse_reader.cpp \
    publisher.cpp

HEADERS += \
    mouse_reader.h \
    publisher.h
