#include "mouse_event_handler.h"

#include <mouse.h>

void mouse_event_handler::data_received(input_event_msg_t msg) {
    if(msg.ev_type == EV_KEY && msg.ev_value == MOUSE_PRESSED) {
        switch(msg.ev_code) {
            case MOUSE_LBTN:
                emit game_command(' ');
                break;
            case MOUSE_MBTN:
            case MOUSE_RBTN:
                emit game_command('q');
                break;
        }
    } else if (msg.ev_type == EV_REL) {
	switch(msg.ev_code) {
            case MOUSE_AXIS_X:
                emit game_command(msg.ev_value>0 ? 'd':'a');
                break;
            case MOUSE_AXIS_Y:
                emit game_command(msg.ev_value>0 ? 's':'w');
                break;
	}
    } 
}
/*
void mouse_event_handler::data_received(input_event_msg_t msg){
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
*/
