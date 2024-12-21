#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <type_traits>
#include <vector>
#include <algorithm>
#include "./Component.h"

class Entity {
public:
    std::string name;
    std::vector<Component*> components;
    Component* addComponent(ComponentId id);
    void removeComponent(ComponentId id);
    void update(Time* time);
    Entity(std::string name);
    ~Entity();
};

#endif
