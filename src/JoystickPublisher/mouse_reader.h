#ifndef MOUSE_READER_H
#define MOUSE_READER_H

#include <QThread>
#include <QSettings>
#include <msg_types.hpp>
#include <linux/input.h> //the struct for input events
#include <fstream>
#include <stdexcept> //to catch fstream exceptions

#include <app.h>


class mouse_reader : public QThread
{
    Q_OBJECT
public:
    mouse_reader();
    ~mouse_reader(){}
signals:
    void mouse_received(input_event_msg_t);
private:
    input_event_msg_t m_event;
    input_event event;
    QSettings settings;
    std::string device_name;

    void run();
};
#endif // MOUSE_READER_H
