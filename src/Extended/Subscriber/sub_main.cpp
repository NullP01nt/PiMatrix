//
//  Weather update client in C++
//  Connects SUB socket to tcp://localhost:5556
//  Collects weather updates and finds avg temp in zipcode
//
//  Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>
//
#include <zmq/zmq.hpp>
#include <iostream>
#include <sstream>

#include <msg_types.hpp>

int main (int argc, char *argv[])
{
    zmq::context_t *context;
	context = new zmq::context_t(1);

    //  Socket to talk to server
    std::cout << "Collecting updates from server…\n" << std::endl;
    zmq::socket_t *subscriber;
	subscriber = new zmq::socket_t(*context, ZMQ_SUB);
    subscriber->connect("tcp://localhost:55555");

	std::string filter_topic = "CTRL";
	subscriber->setsockopt(ZMQ_SUBSCRIBE, filter_topic.c_str(), filter_topic.length());

    //  Subscribe to zipcode, default is NYC, 10001
//    const char *filter = (argc > 1)? argv [1]: "CTRL";
//    subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen (filter));

    //  Process 100 updates
    int update_nbr;
    for (update_nbr = 0; update_nbr < 100; update_nbr++) {

        zmq::message_t update;

        subscriber->recv(&update);

	input_event_msg_t* m_event = reinterpret_cast<input_event_msg_t*>(update.data());

	std::cout << *m_event << std::endl;
    }
    return 0;
}
