#include <iostream>
#include <fstream>
#include <stdexcept>

#include <linux/input.h> //the struct for input events

#include <cstdlib>
#include <string>

#include <zmq/zmq.hpp>
#include <app.h>
#include <QSettings>

#include <msg_types.hpp>

/**
 * Mouse Server application.
 * Reads the device input for a mouse (or controller).
 * Repackage the data to strip the time information
 */

int main(){

    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, ORG_NAME, APP_NAME);
    std::string hostname   = settings.value("subscriber/host","localhost").toString().toStdString();
    std::string topicname  = settings.value("subscriber/topic","HELLO").toString().toStdString();
    int portnumber         = settings.value("subscriber/port",55555).toInt();
    std::string idev_name  = settings.value("subscriber/mouse","/dev/input/event15").toString().toStdString();

    std::string connect_str = "tcp://*:" + std::to_string( portnumber );


    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PUB);
    socket.bind(connect_str);

    struct input_event event;

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
