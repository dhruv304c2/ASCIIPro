#include "ECS/Component.h"
#include "Core/Game.h"
#include "Core/Input/InputManager.h"
#include "Core/Window.h"
#include "ECS/Entity.h"
#include <cassert>
#include <vector>

Component::Component(void* ent_ptr){
    attachToEnt(ent_ptr);
    auto ent = static_cast<Entity*>(entity_ptr);
    game_ptr = ent -> gamePtr();
}

Component::~Component() {}

void Component::update(Time& time){};

void Component::update(){};

void Component::start(){};

bool Component::isAttached(Component* comp){
    for(auto c : attached()){
        if(c == comp) return true;
    }
    return false;
}

std::vector<Component*> Component::attached(){
    return static_cast<Entity*>(entity_ptr) -> components;
}

std::vector<Component*> Component::all(){
    return static_cast<Game*>(game_ptr) -> allComponents();
}

InputManager* Component::input(){
    return static_cast<Game*>(game_ptr) -> input();
}

Window* Component::window(){
    return static_cast<Game*>(game_ptr) -> window();
}

void Component::attachToEnt(void* ent_ptr){
    assert(ent_ptr != nullptr);
    assert(static_cast<Entity*>(ent_ptr));
    entity_ptr = ent_ptr;
}
