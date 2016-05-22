#include <QCoreApplication>
#include <msg_types.hpp>

/**
 * Input Server application.
 * Reads the device input for a mouse and controller.
 * mouse_reader and gamepad_reader reads the device files in seperate threads.
 * publisher receives QtSignals with the package and sends it over ZMQ
 */

#include "publisher.h"
#include "mouse_reader.h"

Q_DECLARE_METATYPE( input_event_msg_t )

int main(int argc, char* argv[]){

    qRegisterMetaType<input_event_msg_t>();
    publisher a(argc,argv);

    mouse_reader mouse;
//    gamepad_reader gamepad;

    QObject::connect(&mouse,SIGNAL(mouse_received(input_event_msg_t)),&a,SLOT(data_received(input_event_msg_t)));
//    QObject::connect(&gamepad,SIGNAL(gamepad_received(input_event_msg_t)),&a,SLOT(data_received(input_event_msg_t)));
    mouse.start();

    return a.exec();
}
