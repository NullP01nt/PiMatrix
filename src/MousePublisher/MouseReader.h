#pragma once

#include <QThread>
#include <QSettings>
#include <msg_types.hpp>
#include <mouse.h>
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
    void mouse_event(input_event_t ev);
private:
	void loadSettings(void);

//    input_event_msg_t m_event;
    input_event_t event;
    QSettings settings;
    std::string device_name;

    void run();
};
