#ifndef WORKER_H
#define WORKER_H

#include <QCoreApplication>
#include <msg_types.hpp>
#include <unistd.h>
#include <iostream>

//core application. Can print the message
class worker : public QCoreApplication{
    Q_OBJECT
private:
//    void sig_handler(int param){
//	emit close(); 
//    } 
//    signal(SIGINT, sig_handler);
public:
    worker(int &argc, char **argv): QCoreApplication(argc,argv){}
    ~worker(){}
signals:
    void close();
public slots:
    void data_received(input_event_msg_t msg);
};


#endif // WORKER_H
