#include "../.././includes/ECS/Component.h"

Component::Component(){}

Component::~Component() {}

void Component::update(Time* time, std::vector<Component*>){};

bool Component::isAttached(Component* comp){
    for(auto c : attached){
        if(c == comp) return true;
    }
    return false;
}
