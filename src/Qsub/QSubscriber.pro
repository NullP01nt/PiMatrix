######################################################################
# Automatically generated by qmake (3.0) Fri May 20 15:47:05 2016
######################################################################

TEMPLATE = app
TARGET = QSubscriber
INCLUDEPATH += .

include($$PWD/../Extended/common.pri)

MOC_DIR=$$PWD/moc
OBJECTS_DIR=$$PWD/objs

# Input
HEADERS += app.h \
    receiver.h \
    worker.h
SOURCES += sub_main.cpp \
    receiver.cpp \
    worker.cpp
