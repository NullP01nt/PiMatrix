#include <iostream>
#include <fstream>
#include <stdexcept>

#include <linux/input.h> //the struct for input events

#include <cstdlib>
#include <string>

#include <zmq/zmq.hpp>
#include "../mouse/message.hpp"

/**
 * Mouse client application.
 * Receives the mouse package over zmq
 * Enterprets the data and prints what was sent.
 */

int main(){
    int x_pos = 0, y_pos = 0;

    const int y_max = 400;
    const int x_max = 800;

    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_SUB);
    socket.setsockopt(ZMQ_IDENTITY, "Hello", 5);
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket.connect("tcp://localhost:5555");

    zmq::message_t incomming_message (sizeof(message));

    while(true){
        socket.recv(&incomming_message);
        message event = *static_cast<struct message*>(incomming_message.data());
        if (event.type == 2) {
            if (event.code == 0) x_pos += event.value;
            if (event.code == 1) y_pos += event.value;

            if(x_pos> x_max) x_pos =  x_max;
            if(x_pos<-x_max) x_pos = -x_max;
            if(y_pos> y_max) y_pos =  y_max;
            if(y_pos<-y_max) y_pos = -y_max;
            std::cout << " x " << x_pos
                      << " y " << y_pos
                      << std::endl;
        } else if (event.type == 1) {
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
    return 0;
}
