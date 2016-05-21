#pragma once

#include <QtCore>
#include <QThread>

class gui_updater : public QThread
{
    Q_OBJECT
private:
    unsigned long _delay;
public:
    gui_updater(): _delay(1000){}
    gui_updater(unsigned long delay): _delay(delay){}
    void set_delay(unsigned long delay){_delay = delay;}
    virtual ~gui_updater(){}
signals:
    void update();

protected:
    void run(){
        while(true){
            QThread::msleep(_delay);
            emit update();
        }
    }

};
