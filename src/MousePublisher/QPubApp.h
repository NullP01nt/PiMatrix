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
#include "app.h"

class QPubApp: public QCoreApplication{
    Q_OBJECT
public:
    QPubApp(int &argc, char **argv);
    ~QPubApp();
public slots:
    void data_received(input_event_msg_t msg);
private:
	void loadSettings(void);
	void initSocket(void);

	std::string connect_str;

	QSettings settings;
	std::string hostname;
	int portnumber;

    zmq::context_t	*zmq_context = nullptr;
    zmq::socket_t	*zmq_socket = nullptr;
};
