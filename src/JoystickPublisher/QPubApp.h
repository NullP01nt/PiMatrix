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
#include <joystick.h>
#include "app.h"
#include "JoystickReader.h"

class QPubApp: public QCoreApplication {
    Q_OBJECT
public:
    QPubApp(int &argc, char **argv);
    ~QPubApp();
public slots:
	void new_input(js_event_t ev);
private:
	void loadSettings(void);
	int initSocket(void);

	JoystickReader joystick;

	std::string connect_str;

    QSettings settings;
	std::string			hostname;
    int					portnumber;
	std::string topic_name;

	input_event_msg_t msg;

    zmq::context_t		*zmq_context=nullptr;
    zmq::socket_t		*zmq_socket=nullptr;
};
