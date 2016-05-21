#include "event_handler.h"

event_handler::event_handler() :
    context (1),
    socket (context, ZMQ_SUB),
    incomming_message (sizeof(message)){
    socket.setsockopt(ZMQ_IDENTITY, "Hello", 5);
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket.connect("tcp://localhost:5555");
}

void event_handler::run() {
    while(true){
        socket.recv(&incomming_message);
        message event = *static_cast<struct message*>(incomming_message.data());
        if (event.type == 2) {
            if (event.code == 0) {
                if(event.value > 0) {
                    emit game_command('d'); //++x
                } else {
                    emit game_command('a'); //--x
                }
            }
            if (event.code == 1) {
                if(event.value > 0) {
                    emit game_command('s'); //++y
                } else {
                    emit game_command('w'); //--y
                }
            }
        } else if (event.type == 1) {
            if (event.value == 1){ //pressed
                if(event.code == 272){
                    emit game_command(' '); // left btn resumes
                } else if(event.code == 273){
                    emit game_command('p'); // right btn pauses
                } else if(event.code == 274){
                    emit game_command('q'); // mid btn resets
                }
            }
//            if (event.value == 0); //released
        }
    }
    QThread::exit();
}
