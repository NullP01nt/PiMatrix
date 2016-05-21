#include "worker.h"
#include "receiver.h"
#include <msg_types.hpp>

Q_DECLARE_METATYPE( input_event_msg_t )

int main(int argc, char **argv) {
    qRegisterMetaType<input_event_msg_t>();
    worker a(argc,argv);
    receiver rec;

    QObject::connect(&rec, SIGNAL(data_received(input_event_msg_t)),&a,SLOT(data_received(input_event_msg_t)));
    rec.start();

    return a.exec();
}
