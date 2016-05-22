// Std includes

// Qt includes
#include <QObject>
#include <QCoreApplication>

// SDU-EMB4 includes
#include "QPubApp.h"
#include <joystick.h>
#include "JoystickReader.h"

/**
 * Input Server application.
 * Reads the device input for a mouse and controller.
 * mouse_reader and gamepad_reader reads the device files in seperate threads.
 * publisher receives QtSignals with the package and sends it over ZMQ
 */

Q_DECLARE_METATYPE( js_event_t )
Q_DECLARE_METATYPE( input_event_msg_t )

int main(int argc, char* argv[]){

    qRegisterMetaType<js_event_t>();
    QPubApp a(argc,argv);

    JoystickReader joystick;

    QObject::connect(&joystick,SIGNAL(joystick_event(js_event_t)),&a,SLOT(new_input(js_event_t)));
	joystick.start();

    return a.exec();
}
