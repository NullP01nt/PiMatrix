#pragma once

#include <QtCore>
#include <QObject>
#include <zmq/zmq.hpp>
#include <msg_types.hpp>


class joystick_event_handler : public QObject
{
    Q_OBJECT
public:
    joystick_event_handler(){}
//    virtual ~event_handler(){}

signals:
    void game_command(char);

public slots:
    void data_received(input_event_msg_t msg);

};

