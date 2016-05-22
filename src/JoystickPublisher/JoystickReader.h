#pragma once

#include <QThread>
#include <QSettings>
#include <msg_types.hpp>
#include <linux/input.h> //the struct for input events
#include <fstream>
#include <stdexcept> //to catch fstream exceptions

#include "app.h"

class JoystickReader : public QThread
{
    Q_OBJECT
public:
    JoystickReader();
    ~JoystickReader(){}
signals:
    void input_event(void *event);
private:
    input_event_msg_t m_event;
    input_event event;
    QSettings settings;
    std::string device_name;

    void run();
};
