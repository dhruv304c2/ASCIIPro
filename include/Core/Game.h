#ifndef GAME_H
#define GAME_H
#include "Core/Input/InputManager.h"
#include "ECS/Entity.h"
#include "Time.h"
#include <vector>

class Game {
public:
    Game(float delta);
    ~Game();
    Entity* createEntity(std::string name);
    void run();
    std::vector<Component*> allComponents();
private:
    Time* time;
    InputManager* input;
    std::vector<Entity*> entities;
};

#endif 
