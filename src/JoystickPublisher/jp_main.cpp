// Std includes

// Qt includes
#include <QObject>
#include <QCoreApplication>

// SDU-EMB4 includes
#include "QPubApp.h"
#include <msg_types.hpp>
#include "JoystickReader.h"

/**
 * Input Server application.
 * Reads the device input for a mouse and controller.
 * mouse_reader and gamepad_reader reads the device files in seperate threads.
 * publisher receives QtSignals with the package and sends it over ZMQ
 */

Q_DECLARE_METATYPE( input_event_msg_t )

int main(int argc, char* argv[]){

    qRegisterMetaType<input_event_msg_t>();
    QPubApp a(argc,argv);

    JoystickReader joystick;

    QObject::connect(&joystick,SIGNAL(input_event(void*)),&a,SLOT(data_received(void*)));
	joystick.start();

    return a.exec();
}
