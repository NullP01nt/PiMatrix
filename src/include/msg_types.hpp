#pragma once
#include <cstdint>
#include <sstream>

typedef struct input_event_msg {
	uint8_t		topic[4];
	uint16_t	dev_type;
	uint16_t	dev_model;
	uint16_t	ev_type;
	uint16_t	ev_code;
	int32_t 	ev_value;

	friend std::ostream & operator<< (std::ostream &out, input_event_msg &msg) {
		out << "[";
		out << msg.topic[0] << msg.topic[1] << msg.topic[2] << msg.topic[3];
		out << "] dt: ";
		out << msg.dev_type;
		out << ", dm: ";
		out << msg.dev_model;
		out << ", et: ";
		out << msg.ev_type;
		out << ", ec: ";
		out << msg.ev_code;
		out << ", ev: ";
		out << msg.ev_value;
		return out;
	}
} input_event_msg_t;
