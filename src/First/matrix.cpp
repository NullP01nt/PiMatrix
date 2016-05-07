#include <iostream>
#include "matrix.h"

Matrix::Matrix(void) {};
Matrix::~Matrix(void) {};

void Matrix::writeDisplay(void) {
	for(int y=0; y<8; y++) {
		for(int x=0; x<16; x++) {
			std::cout << (displaybuffer[y]&(1<<(16-x)) ? "1" : "0");
		}
		std::cout << std::endl;
	}
}

void Matrix::clear(void) {
	for(int y=0; y<8; y++) {
		displaybuffer[y] = 0x0000;
	}
}
