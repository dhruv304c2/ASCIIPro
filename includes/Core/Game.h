#ifndef GAME_H
#define GAME_H
#include "Time.h"
#include <vector>
#include "../ECS/Entity.h"

class Game {
public:
    Game(Time* time, float delta);
    ~Game();
    Entity* createEntity(std::string name);
    void run();
private:
    Time* time;
    std::vector<Entity*> entities;
};

#endif 
