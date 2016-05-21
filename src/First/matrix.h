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
#include "../First/pos.hpp"

#define HT16K33_BLINK_CMD			0x80
#define HT16K33_BLINK_DISPLAYON		0x01
#define HT16K33_BLINK_OFF			0x00
#define HT16K33_BLINK_2HZ			0x01
#define HT16K33_BLINK_1HZ			0x02
#define HT16K33_BLINK_HALFHZ		0x03

#define HT16K33_CMD_BRIGHTNESS		0xE0

class Matrix {
public:
	Matrix(void);
	~Matrix(void);

	void writeDisplay(void);
	void clear(void);

	void clearRow(uint8_t rowIdx);
	void fillRow(uint8_t rowIdx);

    void turn_on(pos point){
        uint8_t x = 16 - point.x;
        displaybuffer[point.y] = displaybuffer[point.y] | 1 << x;
    }
    void turn_off(pos point){
        uint8_t x = 16 - point.x;
        displaybuffer[point.y] = displaybuffer[point.y] & !(1 << x);
    }
    u_int16_t status(pos point){
        uint8_t x = 16 - point.x;
        return displaybuffer[point.y] & (1 << x);
    }
    void flip(pos point){
        if(status(point)){
            turn_off(point);
        } else {
            turn_on(point);
        }
    }


protected:
	uint8_t		i2c_addr;
	uint16_t	displaybuffer[8];
};

#endif
