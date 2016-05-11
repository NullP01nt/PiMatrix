#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <list>
#include "pos.hpp"

enum direction {north, south, east, west};
enum gamestate {running, paused, gameover};

class snake {
public:
    snake():
        game_width(16),
        game_height(8),
        body(),
        berry(),
        dir(),
        moving_dir(),
        state(paused){
        init_snake(3,pos(game_width/2,game_height/2));
        generate_berry();
    }

    void set_direction(direction new_movement_dir){
        if(new_movement_dir != opposite_direction(moving_dir)){
            dir = new_movement_dir;
        }
    }

    void set_game_state(gamestate new_state){
        state = new_state;
    }

private:
    void move_snake(){
        pos new_head = *body.begin();

        switch (direction){
        case north :
            new_head.y--;
            break;
        case south :
            new_head.y++;
            break;
        case east :
            new_head.x++;
            break;
        case west :
            new_head.x--;
            break;
        default:
            break;
        }
        moving_dir = direction;

        body.push_front(new_head);

        if(new_head == berry){
            generateBerry();
        } else{
            _snake.pop_back();
        }
    }

    bool in_collision(pos &p){
        if(p == *body.begin()){
            return true;
        } else {
            for(std::list< point >::iterator t = ++_snake.begin(); t != _snake.end(); ++t){
                if(p == *t){
                    return true;
                }
            }
        }
        return false;
    }

    void generate_berry(){
        bool valid_berry = false;
        pos berry_pos;
        while(!valid_berry) {
            berry.rand_point(game_width, game_height);
            valid_berry = !in_collision(berry_pos);
        }
        berry = berry_pos;
    }

    void init_snake(size_t size,pos head){
        body.clear();
        body.resize(size);
        pos p(head);
        for(std::list< point >::iterator sn = body.begin(); sn != body.end(); ++sn){
            *sn = p;
            p.y++;
        }
    }

    direction opposite_direction(direction &new_dir){
        direction ret = new_dir;
        switch(new_dir){
        case north:
            ret = south;
            break;
        case south:
            ret = north;
            break;
        case east:
            ret = west;
            break;
        case west:
            ret = east;
            break;
        default:
            break;
        }
        return ret;
    }
    u_int8_t game_height, game_width;
    std::list<pos> body;
    pos berry;

    direction dir, moving_dir;
    gamestate state;
};

#endif // SNAKE_HPP
