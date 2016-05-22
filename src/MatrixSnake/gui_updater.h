#pragma once

#include <QtCore>
#include <QThread>


class gui_updater : public QThread
{
    Q_OBJECT
private:
    bool running;
    unsigned long _delay;
public:
    gui_updater():
	running(true),
	_delay(1000){}
    gui_updater(unsigned long delay): 
	running(true),
	_delay(delay){}
    virtual ~gui_updater(){}
    void set_delay(unsigned long delay){_delay = delay;}
signals:
    void update();

protected:
    void run(){
        while(running){
            QThread::msleep(_delay);
            emit update();
        }
	QThread::exit();
    }
public slots:
    void cleanup(void){
	running = false;
    }
};
