#include <iostream>
#include <fstream>
#include <stdexcept>

#include <linux/input.h> //the struct for input events
#include <cstdlib>
#include <string>

int main(){
    struct input_event event;
    int x_pos = 0, y_pos = 0;

    const int y_max = 400;
    const int x_max = 800;

    std::string idev_name;
    idev_name = std::string(getenv("MOUSE_INPUT_DEV"));
    std::cout << idev_name << std::endl;
		

    while(true){

        std::ifstream file;
        file.open(idev_name);

        if(!file.good()){
            throw( std::runtime_error("opening device, do you have permission?") );
        }

        while( file.read(reinterpret_cast<char*>(&event),sizeof(struct input_event)) ) {
            if (event.type == 2) {
                if (event.code == 0) x_pos += event.value;
                if (event.code == 1) y_pos += event.value;

                if(x_pos> x_max) x_pos =  x_max;
                if(x_pos<-x_max) x_pos = -x_max;
                if(y_pos> y_max) y_pos =  y_max;
                if(y_pos<-y_max) y_pos = -y_max;
                std::cout << event.time.tv_sec << "." << event.time.tv_usec
                          << " x " << x_pos
                          << " y " << y_pos
                          << std::endl;
            } else if (event.type == 1) {
                std::cout << event.time.tv_sec << "." << event.time.tv_usec << " ";
                switch(event.code){
                case 272:
                    std::cout << "Left btn ";
                    break;
                case 273:
                    std::cout << "Right btn ";
                    break;
                case 274:
                    std::cout << "Mid btn ";
                    break;
                default:
                    std::cout << event.code << "Unknown event ";
                    break;
                }
                if (event.value == 0) std::cout << "released!!\n";
                if (event.value == 1) std::cout << "pressed!!\n";
            }
        }
        file.close();
    }
    return 0;
}
