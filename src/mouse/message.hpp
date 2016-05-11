#pragma once

#include <sstream>

struct message{
    unsigned short type;
    unsigned short code;
    int value;

    friend std::ostream & operator<< (std::ostream &out, message &t){
        out << "type ";
        out << t.type;
        out << " code ";
        out << t.code;
        out << " value ";
        out << t.value;
        return out;
    }
};
