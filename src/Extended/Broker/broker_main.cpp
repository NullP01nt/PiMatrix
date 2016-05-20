#include <iostream>
#include <cstdint>

#include <zmq/zmq.hpp>

using std::cout;
using std::endl;

int main() {
        zmq::context_t ctx(1);
        zmq::socket_t frontend(ctx, ZMQ_XSUB);
        zmq::socket_t backend(ctx, ZMQ_XPUB);
        frontend.bind("tcp://*:55554");
        backend.bind("tcp://*:55555");
        zmq::proxy(static_cast<void*>(frontend),static_cast<void*>(backend),nullptr);
        return 0;
}
