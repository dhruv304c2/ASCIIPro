#include "ECS/Component.h"

Component::Component(){}

Component::~Component() {}

void Component::update(Time* time, std::vector<Component*> components, InputManager* input){};

bool Component::isAttached(Component* comp){
    for(auto c : attached){
        if(c == comp) return true;
    }
    return false;
}
