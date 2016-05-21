#pragma once

#include "../First/matrix.h"
#include "../First/snake.hpp"
#include "../First/pos.hpp"

#include <QtCore>
#include <QThread>

class gui : public QThread, public snake
{
    Q_OBJECT
private:
    Matrix m;
    gamestate state;
public:
    gui():
    m(),
    state(paused){
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
