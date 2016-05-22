#include <wiringPi.h>
#include <wiringPiI2C.h>

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <unistd.h>

int main() {
	uint16_t buffer[8] = {  0xFF00, 0x00FF, 0xFF00, 0x00FF,
		   		0xFF00, 0x00FF, 0xFF00, 0x00FF};

	int fd = -1;
	fd = wiringPiI2CSetup(0x70);
	std::cout << fd << std::endl;
	
	wiringPiI2CWrite(fd,0x21);
	wiringPiI2CWrite(fd,0x81);
	wiringPiI2CWrite(fd,0xEF);

	int mem_addr=0x00;
	for(int row = 0; row < 8; row++ ) {
		std::cout << std::hex << std::setfill('0') << std::setw(2) << mem_addr << " " << std::setw(4) << (buffer[row]&0x00FF) << std::endl;
		wiringPiI2CWriteReg8(fd, mem_addr++, buffer[row]&0x00FF);
		std::cout << std::hex << std::setfill('0') << std::setw(2) << mem_addr << " " << std::setw(4) << ((buffer[row]>>8)&0x00FF) << std::endl;
		wiringPiI2CWriteReg8(fd, mem_addr++, (buffer[row]>>8)&0x00FF);
	}

	sleep(1);

#define DISP_ON 0x81
#define BLINK_GAME_OVER (DISP_ON | 0x04)
#define BLINK_PAUSE (DISP_ON | 0x02)
//	wiringPiI2CWrite(fd,BLINK_GAME_OVER);
//	sleep(7);
//	wiringPiI2CWrite(fd,BLINK_PAUSE);

//	wiringPiI2CWrite(fd, 0x80);

	return 0;
}
