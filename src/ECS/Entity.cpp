#include "ECS/Entity.h"
#include "Components/Transform.h"
#include "ECS/Component.h"
#include <string>
#include <vector>

Entity::Entity(std::string name) {
    this ->name = std::move(name);
    Transform* transform = dynamic_cast<Transform*>(addComponent<Transform>());
    transform -> position = Vector2D<float>(0,0);
}

void Entity::update(Time* time, std::vector<Component*> all, InputManager* input){
    for(auto c: components){
        c ->update(time, all, input);
    }
}

Entity::~Entity() {
    for(auto c : components){
	delete c;
    }
    components.clear();
}

