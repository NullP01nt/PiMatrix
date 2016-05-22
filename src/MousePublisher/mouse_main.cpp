// Std includes

// Qt includes
#include <QObject>
#include <QCoreApplication>

// SDU-EMB4 includes
#include <mouse.h>
#include "QPubApp.h"
#include "MouseReader.h"

Q_DECLARE_METATYPE( input_event_t )
Q_DECLARE_METATYPE( input_event_msg_t )

int main(int argc, char* argv[]){

    qRegisterMetaType<input_event_t>();
    QPubApp a(argc,argv);

    MouseReader mouse;

    QObject::connect(&mouse,SIGNAL(mouse_event(input_event_t)),&a,SLOT(new_input(input_event_t)));
	mouse.start();

    return a.exec();
}
