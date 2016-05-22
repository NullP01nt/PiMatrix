#pragma once

// Std
#include <stdexcept> //to catch fstream exceptions
#include <fstream>

// Qt
#include <QThread>
#include <QSettings>

// SDU-EMB4
#include <msg_types.hpp>
#include <joystick.h>
#include "app.h"

class JoystickReader : public QThread
{
    Q_OBJECT
public:
    JoystickReader();
    ~JoystickReader();
signals:
    void joystick_event(js_event_t ev);
private:
	void loadSettings(void);

	js_event_t event;
    QSettings settings;
    std::string device_name;

    void run();
};
