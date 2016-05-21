#include <iostream>
#include <fstream>
#include <stdexcept>

#include <linux/input.h> //the struct for input events

#include <cstdlib>
#include <string>

#include <zmq/zmq.hpp>

#include "message.hpp" //event without time information


/**
 * Mouse Server application.
 * Reads the device input for a mouse (or controller).
 * Repackage the data to strip the time information
 */

int main(){
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PUB);
    socket.bind("tcp://*:5555");

    struct input_event event;

    std::string idev_name;
    try {
        idev_name = std::string(getenv("MOUSE_INPUT_DEV"));
    } catch(std::logic_error) {
        idev_name = "/dev/input/event15"; //mice and event* does not use the same format!
    }

    while(true){

        std::ifstream file;
        file.open(idev_name);

        if(!file.good()){
            throw( std::runtime_error("opening device, do you have permission?") );
        }

        while( file.read(reinterpret_cast<char*>(&event),sizeof(struct input_event)) ) {
            message m_event = {event.type,event.code,event.value};

            zmq::message_t out_going_message (sizeof(message));
            memcpy (out_going_message.data (), &m_event, sizeof(message));
            socket.send (out_going_message);
        }
        file.close();
    }
    return 0;
}
