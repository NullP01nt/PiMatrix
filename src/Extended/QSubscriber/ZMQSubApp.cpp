#include "ZMQSubApp.h"
#include <iostream>

#include <msg_types.hpp>

ZMQSubApp::ZMQSubApp(int &argc, char **argv) : QCoreApplication(argc,argv) {
    zmq_context = new zmq::context_t(1);
    loadSettings();
    if(initSocket()==-1) {
        throw "Could not initialize socket!!";
    }
}

ZMQSubApp::~ZMQSubApp(void) {
    std::cerr << TAG << " ~ZMQSubApp(void)" << std::endl << std::endl;
    delete socket_notifier;
    zmq_socket->close();
    zmq_context->close();
}


void ZMQSubApp::loadSettings(void) {
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, ORG_NAME, APP_NAME);
    hostname = settings.value("subscriber/host","localhost").toString().toStdString();
    topicname = settings.value("subscriber/topic","HELLO").toString().toStdString();
    portnumber = settings.value("subscriber/port",55555).toInt();
}

int ZMQSubApp::initSocket(void) {
    connect_str = "tcp://" + hostname + ":" + std::to_string( portnumber );

    zmq_socket = new zmq::socket_t(*zmq_context, ZMQ_SUB);
    zmq_socket->connect(connect_str);
    zmq_socket->setsockopt(ZMQ_SUBSCRIBE,topicname.c_str(), topicname.length()+1);

    socket_fd_size = sizeof(socket_fd);
    zmq_socket->getsockopt(ZMQ_FD, &socket_fd, &socket_fd_size);

    socket_notifier = new QSocketNotifier(socket_fd, QSocketNotifier::Read, this);
    connect(socket_notifier, SIGNAL(activated(int)), this, SLOT(data_received(int)),Qt::DirectConnection);
    return 0;
}

void ZMQSubApp::data_received(int fd) {
    socket_notifier->setEnabled(false);

    uint32_t	events;
    size_t		events_size = sizeof(events);
    zmq::message_t message;
    input_event_msg_t* m_event;

    while(1) {
        zmq_socket->getsockopt(ZMQ_EVENTS, &events, &events_size);
        if( ( events & ZMQ_POLLIN ) == 0) {
            std::cerr << TAG << " zmq_data_received() no data" << std::endl;
            break;
        }

        std::cerr << TAG << " zmq_data_received() receive message" << std::endl;
        zmq_socket->recv(&message);
        std::cerr << TAG << " zmq_data_received() interpret message" << std::endl;
        m_event = reinterpret_cast<input_event_msg_t*>(message.data());
        std::cerr << TAG << " " << *m_event << std::endl;
    }

    socket_notifier->setEnabled(true);
}
