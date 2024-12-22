#include "../.././includes/ECS/Entity.h"
#include "../../includes/Components/Transform.h"
#include "../../includes/ECS/Component.h"
#include <string>
#include <vector>

Entity::Entity(std::string name) {
    this ->name = name;
    Transform* transform = dynamic_cast<Transform*>(addComponent<Transform>());
    transform -> position = Vector2D(0,0);
}

void Entity::update(Time* time, std::vector<Component*> all){
    for(auto c: components){
        c ->update(time, all);
    }
}

Entity::~Entity() {
    for(auto c : components){
	delete c;
    }
    components.clear();
}

