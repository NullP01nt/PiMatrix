#include "receiver.h"

receiver::receiver() :
    message(sizeof(input_event_msg_t)),
    hostname(""),
    portnumber(0),
    topicname(""),
    connect_str(""),
    zmq_context(1),
    zmq_socket(zmq_context,ZMQ_SUB)
{
    loadSettings();
    if(initSocket()==-1) {
        throw "Could not initialize socket!!";
    }
}
receiver::~receiver(){
    zmq_socket.close();
    zmq_context.close();
}

void receiver::loadSettings(void) {
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, ORG_NAME, APP_NAME);
    hostname = settings.value("subscriber/host","localhost").toString().toStdString();
    topicname = settings.value("subscriber/topic","CTRL").toString().toStdString();
    portnumber = settings.value("subscriber/port",55555).toInt();
}

int receiver::initSocket(void) {
    connect_str = "tcp://" + hostname + ":" + std::to_string( portnumber );

    zmq_socket.connect(connect_str);
  //  zmq_socket.setsockopt(ZMQ_SUBSCRIBE,topicname.c_str(), topicname.length()+1);
    zmq_socket.setsockopt(ZMQ_SUBSCRIBE,"", 0);
    return 0;
}

void receiver::run(){
    std::cout << "starting receiver" << std::endl;
    while(true){
        zmq_socket.recv(&message);
        m_event = *static_cast<input_event_msg_t*>(message.data());
        if(m_event.dev_type == 1){
            emit mouse_received(m_event);
        } else {
            emit game_pad_received(m_event);
        }
    }
    QThread::exit();
}
