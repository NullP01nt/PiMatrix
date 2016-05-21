#pragma once
#include <QObject>
#include <QCoreApplication>
#include <QSettings>
#include <QSocketNotifier>

#include <string>
#include <cstdint>

#include <zmq/zmq.hpp>
#include "app.h"

class ZMQSubApp : public QCoreApplication {
	Q_OBJECT
public:
        ZMQSubApp(int &argc, char **argv);
        ~ZMQSubApp(void);

protected:

private:
    void loadSettings(void);
    int initSocket(void);

    std::string hostname;
    uint32_t portnumber;
    std::string topicname;

	std::string connect_str;

	uint32_t		socket_fd;
	size_t			socket_fd_size;
    QSocketNotifier	*socket_notifier = nullptr;
    zmq::context_t	*zmq_context = nullptr;
    zmq::socket_t	*zmq_socket = nullptr;

private slots:
    void data_received(int fd);
};
