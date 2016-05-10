#include <iostream>
#include <fstream>
#include <cstdint>
#include <map>
#include <string>

using std::string;
using std::map;
using std::pair;
using std::cout;
using std::endl;

struct js_event {
	uint32_t time;
	int16_t value;
	uint8_t type;
	uint8_t number;
};

#define JS_EVENT_BUTTON 	0x01
#define JS_EVENT_AXIS 		0x02
#define JS_EVENT_INIT 		0x80


struct js_event e;

int main(int argc, char **argv) {
	map <uint32_t, string> JS_KEYS;
	JS_KEYS.insert( pair<uint32_t,string>(0,"KEY_SELECT") );
	JS_KEYS.insert( pair<uint32_t,string>(1, "KEY_L3") );
	JS_KEYS.insert( pair<uint32_t,string>(2, "KEY_R3") );
	JS_KEYS.insert( pair<uint32_t,string>(3, "KEY_START") );
	JS_KEYS.insert( pair<uint32_t,string>(4, "KEY_UP") );
	JS_KEYS.insert( pair<uint32_t,string>(5, "KEY_RIGHT") );
	JS_KEYS.insert( pair<uint32_t,string>(6, "KEY_DOWN") );
	JS_KEYS.insert( pair<uint32_t,string>(7, "KEY_LEFT") );
	JS_KEYS.insert( pair<uint32_t,string>(8, "KEY_L2") );
	JS_KEYS.insert( pair<uint32_t,string>(9, "KEY_R2") );
	JS_KEYS.insert( pair<uint32_t,string>(10, "KEY_L1") );
	JS_KEYS.insert( pair<uint32_t,string>(11, "KEY_R1") );
	JS_KEYS.insert( pair<uint32_t,string>(12, "KEY_TRIANGLE"));
	JS_KEYS.insert( pair<uint32_t,string>(13, "KEY_CIRCLE"));
	JS_KEYS.insert( pair<uint32_t,string>(14, "KEY_CROSS"));
	JS_KEYS.insert( pair<uint32_t,string>(15, "KEY_SQUARE"));
	JS_KEYS.insert( pair<uint32_t,string>(16, "KEY_PS_BUTTON"));

	std::ifstream js0;


	js0.open("/dev/input/js0");

	while(1) {
		js0.read((char*)&e, sizeof(e));
		uint32_t key_code = (uint32_t)e.number;
		uint32_t key_value = (uint32_t)e.value;
		if (e.type == JS_EVENT_BUTTON) {
			if(JS_KEYS.count(key_code)>0) {
				std::cout << "[" << e.time << "] (JS_EVENT_BUTTON) " << JS_KEYS[key_code] << " " << key_value << std::endl;
			} else {
				std::cout << "[" << e.time << "] (JS_EVENT_BUTTON) " << key_code << " " << key_value << std::endl;
			}
		}
	}
	return 0;
}
