#pragma once

#include <matrix.h>
#include <snake.hpp>
#include <pos.hpp>

#include <QtCore>
#include <QThread>

class gui : public QThread, public snake
{
    Q_OBJECT
private:
    Matrix m;
public:
    gui():
    m(){
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
        switch(state){
        case running: std::cout << "running\n"; break;
        case paused: std::cout << "paused\n"; break;
        case gameover: std::cout << "game over\n"; break;
        }

        m.writeDisplay();
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

        default : set_game_state(gameover); break;
        }
    }
};
