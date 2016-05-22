#pragma once

#include <matrix.h>
#include <snake.hpp>
#include <pos.hpp>

#include <QtCore>
#include <QThread>

#define MAX_TIMEOUT 15

class gui : public QThread, public snake
{
    Q_OBJECT
private:
    Matrix m;
    unsigned long timeout;
public:
    gui():
    m(),
    timeout(0){
    }
    ~gui(){}

public slots:
    void update_game(){
        m.clear();
        move_snake();
        for(std::list< pos >::iterator t = body.begin(); t != body.end(); ++t){
            m.turn_on(*t);
        }
        m.turn_on(berry);
        int led_speed = 1;
        switch(state){
        case running:
            led_speed = HT16K33_BLINK_DISPLAYON;
            #ifdef DEBUG
            std::cout << "running\n";
            #endif
            timeout=0;
            break;
        case paused:
            led_speed = HT16K33_BLINK_1HZ;
            #ifdef DEBUG
            std::cout << "paused\n";
            #endif
            timeout++;
            break;
        case gameover:
            led_speed = HT16K33_BLINK_HALFHZ;
            #ifdef DEBUG
            std::cout << "game over\n";
            #endif
            timeout++;
            break;
        }
        if(timeout >= MAX_TIMEOUT){
            m.clear();
            led_speed = HT16K33_BLINK_OFF;
        }
        m.writeDisplay(led_speed);
    }
    void get_input(char key){
        switch(key){
        case 'w': set_direction(north); break;
        case 'a': set_direction(west); break;
        case 's': set_direction(south); break;
        case 'd': set_direction(east); break;
        case ' ':
            if(state == paused){
                set_game_state(running);
            } else {
                set_game_state(paused);
            }
            break;
        case 'p': set_game_state(paused); break;
	case 'q': set_game_state(gameover); break;
        }
    }
};
