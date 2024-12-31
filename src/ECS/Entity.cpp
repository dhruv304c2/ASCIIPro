#include "ECS/Entity.h"
#include "Components/Transform.h"
#include "Core/Game.h"
#include "ECS/Component.h"
#include <cassert>
#include <string>
#include <vector>

Entity::Entity(std::string name, void* game_ptr) {
    this ->name = std::move(name);

    assert(game_ptr != nullptr);
    assert(static_cast<Game*>(game_ptr));
    this -> game_ptr = game_ptr;

    Transform* transform = addComponent<Transform>();
    transform -> position = Vector2D<float>(0,0);
}

void Entity::update(Time* time, InputManager* input){
    for(auto c: components){
        c ->update(time, input);
        c ->update(time);
        c ->update();
    }
}

Entity::~Entity() {
    for(auto c : components){
	delete c;
    }
    components.clear();
}

void* Entity::gamePtr(){
    return game_ptr;
}
