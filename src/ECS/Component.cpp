#include "ECS/Component.h"
#include "Core/Game.h"
#include "ECS/Entity.h"
#include <cassert>
#include <vector>

Component::Component(void* ent_ptr){
    attachToEnt(ent_ptr);
    auto ent = static_cast<Entity*>(entity_ptr);
    game_ptr = ent -> gamePtr();
}

Component::~Component() {}

void Component::update(Time* time, InputManager* input){};

void Component::update(Time* time){};

void Component::update(){};

bool Component::isAttached(Component* comp){
    for(auto c : attached()){
        if(c == comp) return true;
    }
    return false;
}

std::vector<Component*> Component::attached(){
    assert(entity_ptr != nullptr);
    assert(static_cast<Entity*>(entity_ptr));
    auto ent = static_cast<Entity*>(entity_ptr);
    return ent-> components;
}

std::vector<Component*> Component::all(){
    assert(game_ptr != nullptr);
    assert(static_cast<Entity*>(game_ptr));
    auto game = static_cast<Game*>(game_ptr);
    return game -> allComponents();
}

void Component::attachToEnt(void* ent_ptr){
    assert(ent_ptr != nullptr);
    assert(static_cast<Entity*>(ent_ptr));
    entity_ptr = ent_ptr;
}
