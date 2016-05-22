#pragma once

// std includes
#include <iostream>

// Qt5 includes
#include <QCoreApplication>
#include <QSettings>

// ZMQ includes
#include <zmq/zmq.hpp>

// SDU-EMB4 includes
#include <msg_types.hpp>
#include "app.h"


class QPubApp: public QCoreApplication{
    Q_OBJECT
public:
    QPubApp(int &argc, char **argv);
    ~QPubApp(){}
public slots:
    void data_received(input_event_msg_t msg);
private:
    QSettings settings;
    int portnumber;
    zmq::context_t context;
    zmq::socket_t socket;
};

