#include <iostream>
#include <fstream>
#include <stdexcept>

#include <linux/input.h> //the struct for input events

#include <cstdlib>
#include <string>

#include <zmq/zmq.hpp>

//#include "message.hpp" //event without time information
#include <msg_types.hpp> //better message

/**
 * Mouse Server application.
 * Reads the device input for a mouse (or controller).
 * Repackage the data to strip the time information
 */

int main(){
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PUB);
    socket.bind("tcp://*:55555");

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

        input_event_msg_t m_event;

        uint32_t topic_number = 0x4C525443; //not sure what should be here
        memcpy(m_event.topic, &topic_number,4);
        m_event.dev_type  = 0x01; // MOUSE
        m_event.dev_model = 0x01; // Generic

        while( file.read(reinterpret_cast<char*>(&event),sizeof(struct input_event)) ) {

            m_event.ev_type   = event.type;
            m_event.ev_code   = event.code;
            m_event.ev_value  = event.value;

            zmq::message_t out_going_message (sizeof(input_event_msg_t));
            memcpy (out_going_message.data (), &m_event, sizeof(input_event_msg_t));
            socket.send (out_going_message);
            std::cout << m_event << std::endl;
        }
        file.close();
    }
    return 0;
}
