#include "joystick_event_handler.h"

#include <joystick.h>

void joystick_event_handler::data_received(input_event_msg_t msg){
    if (msg.ev_type == JS_EVENT_BUTTON && msg.ev_value == 0) {
		switch(msg.ev_code) {
			case PS3_START:
				emit game_command(' ');
				break;
			case PS3_PS:
				emit game_command('q');
				break;
			case PS3_UP:
				emit game_command('w');
				break;
			case PS3_DOWN:
				emit game_command('s');
				break;
			case PS3_LEFT:
				emit game_command('a');
				break;
			case PS3_RIGHT:
				emit game_command('d');
				break;
			default:
				break;
		}
    }
}

