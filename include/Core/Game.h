#ifndef GAME_H
#define GAME_H
#include "Core/Input/InputManager.h"
#include "Core/Window.h"
#include "ECS/Entity.h"
#include "Time.h"
#include <vector>

class Game {
public:
    Game();
    ~Game();
    Entity* createEntity(std::string name);
    InputManager* input();
    Window* window();
    void run();
    std::vector<Component*> allComponents();
private:
    Window _window;
    GameClock _game_clock;
    InputManager _input;
    std::vector<Entity*> _entities;
};

#endif 
