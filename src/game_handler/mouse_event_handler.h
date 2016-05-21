#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <QtCore>
#include <QObject>
#include <zmq/zmq.hpp>
#include <msg_types.hpp>


class mouse_event_handler : public QObject
{
    Q_OBJECT
public:
    mouse_event_handler(){}
//    virtual ~event_handler(){}

signals:
    void game_command(char);

public slots:
    void data_received(input_event_msg_t msg);

};

#endif // EVENT_HANDLER_H
