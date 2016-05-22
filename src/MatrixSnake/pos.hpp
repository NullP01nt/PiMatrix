#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

class pos{
public:
  int8_t x, y;

  pos(){}

  pos(int8_t xx, int8_t yy):x(xx),y(yy){}

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
//  std::ostream& operator <<(std::ostream& os, pos& p ){
//      os << " (" << reinterpret_cast<int>(p.x) << "," << reinterpret_cast<int>(p.y) << ") ";
//      return os;
//  }

};
