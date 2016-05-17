#include <iostream>
#include "matrix.h"
#include "gui.hpp"

int main(int argc, char **argv) {
	std::cout << "Hello, Matrix!" << std::endl;
//	Matrix m;
//	m.clear();
/* example
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
*/
    gui game;
    game.get_input(' ');
    game.update_game();
    game.get_input('d');
    game.update_game();
    game.get_input('s');
    game.update_game();
    game.get_input('s');
    game.update_game();
    game.get_input('s');
    game.update_game();
    game.get_input('a');
    game.update_game();
    game.get_input('a');
    game.update_game();
    game.get_input('w');
    game.update_game();

    return 0;
}
