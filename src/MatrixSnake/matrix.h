/*
 *
 * File: matrix.h
 * Author: Xander Bos <xander.g.bos@gmail.com>
 * Description: Header file for the Matrix class
 *
 * Based partially on work by Adafruit:
 *	https://github.com/adafruit/Adafruit_LED_Backpack
 *
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <cstdint>
#include "pos.hpp"

//#define DEBUG

#define HT16K33_BLINK_CMD			0x80
#define HT16K33_BLINK_DISPLAYON		0x01
#define HT16K33_BLINK_OFF			0x00
//#define HT16K33_BLINK_2HZ			0x01
#define HT16K33_BLINK_1HZ			0x03 //pause speed
#define HT16K33_BLINK_HALFHZ		0x05 //game over speed

#define HT16K33_CMD_BRIGHTNESS		0xE0

//for the I2C stuff
#ifndef DEBUG
#include <wiringPi.h>
#include <wiringPiI2C.h>
#endif

class Matrix {
public:
    Matrix(void) :
        i2c_addr(0x70),
        displaybuffer(),
        fd(0)
    {
        #ifndef DEBUG
        fd = wiringPiI2CSetup(i2c_addr);
        std::cout << fd << std::endl;

        wiringPiI2CWrite(fd,0x21); //turn chip on
        wiringPiI2CWrite(fd,HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON); //not blinking
        wiringPiI2CWrite(fd,HT16K33_CMD_BRIGHTNESS | 0xF); //full brightness
        #endif
    }
    ~Matrix(void){

        clear();
        writeDisplay(HT16K33_BLINK_OFF);
    }

    void writeDisplay(int speed) {
    #ifdef DEBUG
        for(uint8_t y=0; y<8; y++) {
            for(uint8_t x=0; x<16; x++) {
                std::cout << (displaybuffer[y]&(1<<(16-x)) ? "1" : "0");
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    #else
	if (oldbright != bright) {
		wiringPiI2CWrite(fd,0xE0 | bright);
		oldbright = bright;
	}
        wiringPiI2CWrite(fd,HT16K33_BLINK_CMD | speed);
        int mem_addr=0x00;
        for(int row = 0; row < 8; row++ ) {
            wiringPiI2CWriteReg8(fd, mem_addr++, (displaybuffer[row]>>8)&0x00FF);
            wiringPiI2CWriteReg8(fd, mem_addr++, displaybuffer[row]&0x00FF);
        }
    #endif
    }

    void clear(void) {
        for(uint8_t y=0; y<8; y++) {
            clearRow(y);
        }
    }

    void clearRow(uint8_t rowIdx) {
        displaybuffer[rowIdx] = 0x0000;
    }

    void fillRow(uint8_t rowIdx) {
        displaybuffer[rowIdx] = 0xFFFF;
    }

    void turn_on(pos point){
//        uint8_t x = 15 - point.x;
        uint8_t x = point.x;
        displaybuffer[point.y] = displaybuffer[point.y] | 1 << x;
    }
    void turn_off(pos point){
//        uint8_t x = 15 - point.x;
        uint8_t x = point.x;
        displaybuffer[point.y] = displaybuffer[point.y] & !(1 << x);
    }
    u_int16_t status(pos point){
//        uint8_t x = 15 - point.x;
        uint8_t x = point.x;
        return displaybuffer[point.y] & (1 << x);
    }
    void flip(pos point){
        if(status(point)){
            turn_off(point);
        } else {
            turn_on(point);
        }
    }

    void lowerBrightness(void) {
	--bright;
	if (bright==0x00) bright = 0x01;
    }
    
    void raiseBrightness(void) {
	++bright;
	if (bright>=0x10) bright = 0x0F;
    }

protected:
	uint8_t		i2c_addr;
	uint16_t	displaybuffer[8];
    int         fd;

	uint8_t		bright = 0x0F;
	uint8_t		oldbright = 0x0F;
};

#endif
