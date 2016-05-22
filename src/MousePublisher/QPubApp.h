#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <msg_types.hpp>
#include <QCoreApplication>
#include <QSettings>
#include <zmq/zmq.hpp>

#include "app.h"

#include <iostream>

class publisher : public QCoreApplication{
    Q_OBJECT
public:
    publisher(int &argc, char **argv);
    ~publisher(){}
public slots:
    void data_received(input_event_msg_t msg);
private:
    QSettings settings;
    int portnumber;
    zmq::context_t context;
    zmq::socket_t socket;
};


#endif // PUBLISHER_H
