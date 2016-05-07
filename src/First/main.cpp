#include <iostream>
#include "matrix.h"

int main(int argc, char **argv) {
	std::cout << "Hello, Matrix!" << std::endl;
	Matrix m;
	m.clear();
	m.writeDisplay();
	return 0;
}
