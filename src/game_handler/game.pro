######################################################################
# Automatically generated by qmake (3.0) Fri May 20 15:47:05 2016
######################################################################

TEMPLATE = app
TARGET = game 
INCLUDEPATH += .

include($$PWD/../common.pri)

MOC_DIR=$$PWD/moc
OBJECTS_DIR=$$PWD/objs

# Input
HEADERS += \
    receiver.h \
    worker.h\
    matrix.h\
    mouse_event_handler.h\
    gui.h\
    gui_updater.h\
    mouse_event_handler.h

SOURCES += main.cpp \
    receiver.cpp \
    worker.cpp\
    mouse_event_handler.cpp \
