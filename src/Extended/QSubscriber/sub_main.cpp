#include "ZMQSubApp.h"

int main(int argc, char **argv) {
    ZMQSubApp a(argc,argv);

    return a.exec();
}
