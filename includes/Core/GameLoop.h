#ifndef GAMELOOP_H
#define GAMELOOP_H
#include "Time.h"

class GameLoop {
public:
    GameLoop(Time* time);
    ~GameLoop();
    void update();
private:
    Time* time;
};

#endif 
