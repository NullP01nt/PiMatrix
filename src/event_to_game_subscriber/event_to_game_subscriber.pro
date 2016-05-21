#-------------------------------------------------
#
# Project created by QtCreator 2016-05-21T09:55:59
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = event_to_game_subscriber
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    event_handler.cpp\
    ../First/matrix.cpp\

HEADERS += \
    event_handler.h \
    gui.h \
    gui_updater.h

PKGCONFIG += libzmq
CONFIG += link_pkgconfig

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wunused -g
