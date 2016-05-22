#include "mouse_event_handler.h"

#include <iostream>

void mouse_event_handler::data_received(input_event_msg_t msg){
//    std::cout << msg << std::endl;
    if (msg.ev_type == 2) {
        if (msg.ev_code == 0) {
            if(msg.ev_value > 0) {
                emit game_command('d'); //++x
            } else {
                emit game_command('a'); //--x
            }
        }
        if (msg.ev_code == 1) {
            if(msg.ev_value > 0) {
                emit game_command('s'); //++y
            } else {
                emit game_command('w'); //--y
            }
        }
    } else if (msg.ev_type == 1) {
        if (msg.ev_value == 1){ //pressed
            if(msg.ev_code == 272){
                emit game_command(' '); // left btn resumes
            } else if(msg.ev_code == 273){
                emit game_command('p'); // right btn pauses
            } else if(msg.ev_code == 274){
                emit game_command('q'); // mid btn resets
            }
        }
//            if (msg.ev_value == 0); //released
    }
}

