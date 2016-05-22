#include "publisher.h"

publisher::publisher(int &argc, char **argv) :
    QCoreApplication(argc,argv),
    settings(QSettings::NativeFormat, QSettings::UserScope, ORG_NAME, APP_NAME),
    portnumber( settings.value("subscriber/port",55555).toInt() ),
    context(1),
    socket(context, ZMQ_PUB)
{
    std::string connect_str = "tcp://*:" + std::to_string( portnumber );
    socket.bind(connect_str);
}

void publisher::data_received(input_event_msg_t msg) {
    zmq::message_t out_going_message (sizeof(input_event_msg_t));
    memcpy (out_going_message.data (), &msg, sizeof(input_event_msg_t));
    socket.send (out_going_message);
    std::cout << msg << std::endl;
}
