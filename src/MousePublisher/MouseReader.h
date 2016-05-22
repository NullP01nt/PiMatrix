#pragma once

#include <QThread>
#include <QSettings>
#include <msg_types.hpp>
#include <linux/input.h> //the struct for input events
#include <fstream>
#include <stdexcept> //to catch fstream exceptions

#include "app.h"


class MouseReader : public QThread
{
    Q_OBJECT
public:
    MouseReader();
    ~MouseReader();
signals:
    void mouse_event(input_event_msg_t);
private:
    input_event_msg_t m_event;
    input_event event;
    QSettings settings;
    std::string device_name;

    void run();
};
