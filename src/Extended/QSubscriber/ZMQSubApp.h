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
public:
        ZMQSubApp(int &argc, char **argv);
        ~ZMQSubApp(void);

protected:

private:
    void loadSettings();
    int initSocket();

    std::string hostname;
    uint32_t portnumber;
    std::string topicname;

    QSocketNotifier	*_qsn;
    zmq::context_t	*_zmq_ctx;
    zmq::socket_t	*_zmq_sock;
};
