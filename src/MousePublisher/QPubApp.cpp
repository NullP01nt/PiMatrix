#include "QPubApp.h"

#include <QCoreApplication>
#include <msg_types.hpp>

#include <linux/input.h>

QPubApp::QPubApp(int &argc, char **argv) : QCoreApplication(argc,argv), settings(QSettings::NativeFormat, QSettings::UserScope, ORG_NAME, APP_NAME), msg()
{
	zmq_context = new zmq::context_t(1);
	loadSettings();
	initSocket();
}

QPubApp::~QPubApp(void) {
	if( zmq_socket != nullptr ) zmq_socket->close();
	if( zmq_context != nullptr ) zmq_context->close();
}

void QPubApp::loadSettings() {
	hostname = settings.value("publisher/host","localhost").toString().toStdString();
	portnumber = settings.value("publisher/port",55554).toInt();
	topic_name = settings.value("publisher/topic","CTRL").toString().toStdString();
	connect_str = "tcp://" + hostname + ":" + std::to_string( portnumber );

	memcpy(msg.topic, topic_name.c_str(), 4);
	msg.dev_type = DEV_TYPE_MOUSE;
	msg.dev_model = MOUSE_GENERIC;
}

int QPubApp::initSocket() {
	zmq_socket = new zmq::socket_t(*zmq_context, ZMQ_PUB);
	zmq_socket->connect( connect_str );
	return 0;
}

void QPubApp::new_input(input_event_t ev) {
	msg.ev_type = ev.type;
	msg.ev_code = ev.code;
	msg.ev_value = ev.value;

    zmq::message_t out_going_message (sizeof(input_event_msg_t));
    memcpy (out_going_message.data (), &msg, sizeof(input_event_msg_t));
    zmq_socket->send (out_going_message);
    std::cout << msg << std::endl;
}
