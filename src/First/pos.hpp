#pragma once

#include <cstdlib>

class pos{
private:
  u_int8_t x, y;
public:

  pos(){}

  pos(u_int8_t x, u_int8_t y):x(x),y(y){}

  pos(const pos &other){
      x = other.x;
      y = other.y;
  }

  bool operator==(const pos &other) const{
      bool ret = false;
      if(x == other.x && y == other.y){
          ret = true;
      }
      return ret;
  }

  void rand_point(int xMax, int yMax){
      x = rand() % xMax;
      y = rand() % yMax;
  }

  bool operator !=(const pos &other){
      return !(*this == other);
  }
};
