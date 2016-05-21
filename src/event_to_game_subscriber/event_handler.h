#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include "../mouse/message.hpp"
#include <QtCore>
#include <QThread>
#include <zmq/zmq.hpp>


class event_handler : public QThread
{
    Q_OBJECT
private:
    zmq::context_t context;
    zmq::socket_t socket;
    zmq::message_t incomming_message;
public:
    event_handler();
    virtual ~event_handler(){}

signals:
    void game_command(char);

public slots:
//    void movePiece(message msg);

protected:
    void run();


};

#endif // EVENT_HANDLER_H
