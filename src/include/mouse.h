#pragma once

#include <linux/input.h>

typedef struct input_event input_event_t;

#define EV_KEY		0x01
#define EV_REL	 	0x02

#define MOUSE_PRESSED	0x01
#define MOUSE_RELEASED	0x00

#define MOUSE_AXIS_X	0x00
#define MOUSE_AXIS_Y	0x01

#define MOUSE_LBTN	272
#define MOUSE_RBTN	273
#define MOUSE_MBTN	274
