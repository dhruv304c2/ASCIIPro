#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <type_traits>
#include <vector>
#include "./Component.h"


class Entity {
public:
    std::string name;
    std::vector<Component*> components;

    template<typename T>
    T* addComponent();

    template<typename T>
    void removeComponent();

    Entity(std::string name);
    ~Entity();
};

#endif
