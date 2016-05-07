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

protected:
	uint8_t		i2c_addr;
	uint16_t	displaybuffer[8];
};

#endif
