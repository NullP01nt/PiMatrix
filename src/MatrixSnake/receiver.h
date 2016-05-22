#ifndef RECEIVER_H
#define RECEIVER_H

#include <QSettings>
#include <QThread>
#include <msg_types.hpp>
#include <zmq/zmq.hpp>
#include <unistd.h>
#include <iostream>

#include "app.h"

class receiver : public QThread
{
    Q_OBJECT
public:
    receiver();
    ~receiver();
signals:
    void mouse_received(input_event_msg_t);
    void game_pad_received(input_event_msg_t);
private:
    input_event_msg_t m_event;
    zmq::message_t message;
    std::string hostname;
    uint32_t portnumber;
    std::string topicname;

    std::string connect_str;

    zmq::context_t zmq_context;
    zmq::socket_t zmq_socket;


    void loadSettings(void);
    int initSocket(void);

    void run();
};

#endif // RECEIVER_H
