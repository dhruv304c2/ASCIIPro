#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include "Core/Input/InputManager.h"
#include "./Component.h"

class Entity {
public:
    std::string name;
    std::vector<Component*> components;

    template <typename T>
    T* addComponent(){
        std::cout << "adding component of type:" << typeid(T).name() << std::endl;
        if(hasComponent<T>()){
            std::ostringstream msg;
            msg << "Component of type" << typeid(T).name() << "already exists on the entity";
            throw std::runtime_error(msg.str());
        }
        Component* component;
        std::cout << "constructing component:" << typeid(T).name() << std::endl;
        component = dynamic_cast<Component*>(new T((void*)this));
        std::cout << "created component component:" << typeid(T).name() << std::endl;
        components.push_back(component);
        return dynamic_cast<T*>(component);
    }

    template <typename T>
    void removeComponent(){
        auto it = std::remove_if(components.begin(), components.end(), [&] (Component* component) {
            if (dynamic_cast<T*>(component)) {
                delete component; 
                return true;
            }
            return false;
        });
        components.erase(it, components.end());
    }


    template <typename T>
    bool hasComponent(){
        for(auto comp : components){
            if(dynamic_cast<T*>(comp)){
                return true;
            }
        }
        return false;
    }

    template <typename T>
    T* getComponent(){
        for(auto comp : components){
            if(auto tComp = dynamic_cast<T*>(comp)){
                return tComp;
            }
        }
        std::ostringstream msg;
        msg << "Component of type" << typeid(T).name() << "already exists on the entity";
        throw std::runtime_error(msg.str());
    }

    void update(Time* time, InputManager* input);

    void* gamePtr();

    Entity(std::string name, void* game_ptr);

    ~Entity();
private:
    void* game_ptr;
};

#endif
