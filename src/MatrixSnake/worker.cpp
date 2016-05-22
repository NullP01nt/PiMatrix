#include "worker.h"

void worker::data_received(input_event_msg_t msg){
    std::cout << msg << std::endl;
}
