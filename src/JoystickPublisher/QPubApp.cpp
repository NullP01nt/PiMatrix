#include "QPubApp.h"

QPubApp::QPubApp(int &argc, char **argv) : QCoreApplication(argc,argv), settings(QSettings::NativeFormat, QSettings::UserScope, ORG_NAME, APP_NAME)
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
	connect_str = "tcp://" + hostname + ":" + std::to_string( portnumber );
}

int QPubApp::initSocket() {
	zmq_socket = new zmq::socket_t(*zmq_context, ZMQ_PUB);
	zmq_socket->connect( connect_str );
	return 0;
}

void QPubApp::data_received(input_event_msg_t msg) {
    zmq::message_t out_going_message (sizeof(input_event_msg_t));
    memcpy (out_going_message.data (), &msg, sizeof(input_event_msg_t));
    zmq_socket->send (out_going_message);
    std::cout << msg << std::endl;
}
