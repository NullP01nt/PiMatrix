#include <QCoreApplication>
#include "../mouse/message.hpp"

#include "gui.h"
#include "gui_updater.h"
#include "event_handler.h"

/*
 * This reads the input over ømq and updates the snake game
 * works with the "mouse" application
 */

int main(int argc, char* argv[]) {
    QCoreApplication application(argc, argv);
    gui game;
    event_handler handler;
    gui_updater updater(1000);

    QObject::connect(&handler, SIGNAL(game_command(char)),&game,SLOT(get_input(char)));
    QObject::connect(&updater, SIGNAL(update()),&game,SLOT(update_game()));

    handler.start();
    updater.start();

    return application.exec();
}
