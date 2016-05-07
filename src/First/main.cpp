#include <iostream>
#include "matrix.h"

int main(int argc, char **argv) {
	std::cout << "Hello, Matrix!" << std::endl;
	Matrix m;
	m.clear();

	for(int y=0; y<8; y++) {
		if(y%2==1) m.fillRow(y);
	}
	m.writeDisplay();
	for(int y=0; y<8; y++) {
		if(y%2==0) m.fillRow(y);
	}
	m.writeDisplay();
	
	
	for(int y=0; y<8; y++) {
		if(y%2==1) m.clearRow(y);
	}
	m.writeDisplay();
	for(int y=0; y<8; y++) {
		if(y%2==0) m.clearRow(y);
	}
	m.writeDisplay();
	
	
	return 0;
}
