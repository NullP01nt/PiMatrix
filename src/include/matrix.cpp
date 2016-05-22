#include <iostream>
#include <matrix.h>

#define DEBUG

Matrix::Matrix(void) {}
Matrix::~Matrix(void) {}

void Matrix::writeDisplay(void) {
#ifdef DEBUG
	for(uint8_t y=0; y<8; y++) {
		for(uint8_t x=0; x<16; x++) {
			std::cout << (displaybuffer[y]&(1<<(16-x)) ? "1" : "0");
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
#else
	for(uint8_t y=0; y<8; y++) {
		// write displaybuffer[y] & 0xFF;
		// write displaybuffer[y] >> 8;
	}
#endif
}

void Matrix::clear(void) {
	for(uint8_t y=0; y<8; y++) {
		clearRow(y);
	}
}

void Matrix::clearRow(uint8_t rowIdx) {
	displaybuffer[rowIdx] = 0x0000;
}

void Matrix::fillRow(uint8_t rowIdx) {
	displaybuffer[rowIdx] = 0xFFFF;
}
