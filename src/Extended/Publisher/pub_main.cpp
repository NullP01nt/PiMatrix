//
//  update server in C++
//  Binds PUB socket to tcp://*:5556
//  Publishes updates
//
#include <iostream>

#include <zmq/zmq.hpp>
#include <cstdio>
#include <cstdint>

#include <unistd.h>

#include <msg_types.hpp>

#define within(num) (int) ((float) num * random () / (RAND_MAX + 1.0))


int main () {
    //  Prepare our context and publisher
    zmq::context_t context (1);
    zmq::socket_t publisher (context, ZMQ_PUB);
//    publisher.connect("tcp://localhost:55554");
    publisher.bind("tcp://*:55555");

    input_event_msg_t m_event;
    uint16_t ev_type;
    uint16_t ev_code;
    int32_t ev_value;

    uint32_t topic_number = 0x4C525443;

    memcpy(m_event.topic, &topic_number,4);

    m_event.dev_type = 0x01; // MOUSE
    m_event.dev_model = 0x01; // Generic

    while (1) {
	
        ev_type = within(0xFFFF);
        ev_code	= within(0xFFFF);
        ev_value = within(0xFFFF);

        m_event.ev_type = ev_type;
        m_event.ev_code = ev_code;
        m_event.ev_value = ev_value;

        //  Send message to all subscribers
        zmq::message_t message(sizeof(input_event_msg_t));
        memcpy(message.data(), &m_event, sizeof(input_event_msg_t));

	std::cout << m_event << std::endl;
        publisher.send(message);
	sleep(2);
    }
    return 0;
}
