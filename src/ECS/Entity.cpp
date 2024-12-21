#include "../.././includes/ECS/Entity.h"
#include "../../includes/Components/Canvas.h"
#include <stdexcept>
#include <string>
#include <vector>

Entity::Entity(std::string name) {
    this ->name = name;
}

Component* Entity::addComponent(ComponentId id){
    Component* component;
    switch (id) {
        case NONE: 
            throw std::runtime_error("Cannot create component with id: NONE");
        case CANVAS:
            component = new Canvas();
    }
    component -> attached = components;
    components.push_back(component);
    return component;
}

void Entity::removeComponent(ComponentId id){
    auto it = std::remove_if(components.begin(), components.end(), [&] (Component* component) {
        if (component->compId() == id) {
            delete component; 
            return true;
        }
        return false;
    });
    components.erase(it, components.end());
}

void Entity::update(Time* time){
    for(auto c: components){
        c ->update(time);
    }
}

Entity::~Entity() {
    for(auto c : components){
	delete c;
    }
    components.clear();
}

