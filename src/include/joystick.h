#pragma once

typedef struct js_event {
	uint32_t time;
	int16_t value;
	uint8_t type;
	uint8_t number;
} js_event_t;

#define JS_EVENT_BUTTON 	0x01
#define JS_EVENT_AXIS 		0x02
#define JS_EVENT_INIT 		0x80

// PS3 Gamepad button defines
#define PS3_SELECT			0x00
#define PS3_L3				0x01
#define PS3_R3				0x02
#define PS3_START			0x03
#define PS3_UP				0x04
#define PS3_RIGHT			0x05
#define PS3_DOWN			0x06
#define PS3_LEFT			0x07
#define PS3_L2				0x08
#define PS3_R2				0x09
#define PS3_L1				0x0A
#define PS3_R1				0x0B
#define PS3_TRIANGLE		0x0C
#define PS3_CIRCLE			0x0D
#define PS3_CROSS			0x0E
#define PS3_SQUARE			0x0F
#define PS3_PS				0x10
