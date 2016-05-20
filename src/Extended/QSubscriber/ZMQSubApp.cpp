#include "ZMQSubApp.h"

ZMQSubApp::ZMQSubApp(int &argc, char **argv) : QCoreApplication(argc,argv) {
    _zmq_ctx = new zmq::context_t(1);
    loadSettings();
    if(initSocket()==-1) {
        throw "Could not initialize socket!!";
    }
}

ZMQSubApp::~ZMQSubApp(void) {
    delete _zmq_sock;
    delete _zmq_ctx;
}

#include <iostream>
#include <cstring>

void ZMQSubApp::loadSettings(void) {
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, ORG_NAME, APP_NAME);
    hostname = settings.value("subscriber/host","localhost").toString().toStdString();
    topicname = settings.value("subscriber/topic","HELLO").toString().toStdString();
    portnumber = settings.value("subscriber/port",55555).toInt();
    std::cout << hostname << ", " << topicname << ", " << portnumber << std::endl;
}

int ZMQSubApp::initSocket(void) {
    _zmq_sock = new zmq::socket_t(*_zmq_ctx, ZMQ_SUB);
    _zmq_sock->setsockopt(ZMQ_SUBSCRIBE,topicname.c_str(), topicname.length()+1);

    return 0;
}
