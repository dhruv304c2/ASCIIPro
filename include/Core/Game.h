#ifndef GAME_H
#define GAME_H

#include "Core/Input/InputManager.h"
#include "Core/Profiler.h"
#include "Core/Rendering/GameRenderer.h"
#include "Core/Rendering/ProfilerRenderer.h"
#include "Core/Rendering/Renderer.h"
#include "Core/Viewport/ViewportManager.h"
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
    ViewportRect window();
    void run();
    std::vector<Component*> allComponents();

    template<typename T>
    std::vector<T*> allComponent(){
        auto all = allComponents();
        std::vector<T*> requested;
        for(Component* comp : all){
            auto converted = dynamic_cast<T*>(comp);
            if(converted){
                requested.push_back(converted);
            }
        }
        return requested;
    }

private:
    Window _window;
    GameClock _game_clock;
    InputManager _input;
    std::vector<Entity*> _entities;
    ViewportManager _viewport_manager;
    Profiler _profiler;

    GameRenderer* _game_renderer;
    ProfilerRenderer* _profiler_renderer;
};

#endif 
