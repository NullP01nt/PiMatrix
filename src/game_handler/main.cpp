#include "worker.h"
#include "receiver.h"
#include "gui.h"
#include "gui_updater.h"
#include "mouse_event_handler.h"
#include <msg_types.hpp>

Q_DECLARE_METATYPE( input_event_msg_t )

int main(int argc, char **argv) {
    qRegisterMetaType<input_event_msg_t>();
    worker a(argc,argv);
//    QCoreApplication a(argc,argv);
    receiver rec;
    gui game;
    mouse_event_handler mouse_handler;
//    gamepad_event_handler gamepad_handler;
    gui_updater updater(1000);

//    QObject::connect(&rec, SIGNAL(data_received(input_event_msg_t)),&a,SLOT(data_received(input_event_msg_t)));
    QObject::connect(&rec, SIGNAL(mouse_received(input_event_msg_t)),&mouse_handler,SLOT(data_received(input_event_msg_t)));
//    QObject::connect(&rec, SIGNAL(game_pad_received(input_event_msg_t)),&gamepad_handler,SLOT(data_received(input_event_msg_t)));
    QObject::connect(&mouse_handler, SIGNAL(game_command(char)),&game,SLOT(get_input(char)));
    QObject::connect(&updater, SIGNAL(update()),&game,SLOT(update_game()));

    rec.start();     //receiver gets the ZMQ message, sends it to handler
                     // handler translates that into game controls, sends input to the game
    updater.start(); //updater controls the speed of the game, making sure the game is printed

    return a.exec();
}
