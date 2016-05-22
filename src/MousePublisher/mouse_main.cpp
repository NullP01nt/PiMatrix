#include <QCoreApplication>
// Std includes

// Qt includes
#include <QObject>
#include <QCoreApplication>

// SDU-EMB4 includes
#include "QPubApp.h"
#include <msg_types.hpp>
#include "MouseReader.h"

Q_DECLARE_METATYPE( input_event_msg_t )

int main(int argc, char* argv[]){

    qRegisterMetaType<input_event_msg_t>();
    QPubApp a(argc,argv);

    MouseReader mouse;

    QObject::connect(&mouse,SIGNAL(mouse_event(void*)),&a,SLOT(data_received(void*)));
	mouse.start();

    return a.exec();
}
