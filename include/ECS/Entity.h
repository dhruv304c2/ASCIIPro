#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include "./Component.h"

class Entity {
public:
    std::string name;
    std::vector<Component*> components;

    template <typename T>
    T* addComponent(){
        if(hasComponent<T>()){
            std::ostringstream msg;
            msg << "Component of type" << typeid(T).name() << "already exists on the entity";
            throw std::runtime_error(msg.str());
        }
        Component* component;
        component = dynamic_cast<Component*>(new T((void*)this));
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

    void update(Time& time);

    void* gamePtr();

    Entity(std::string name, void* game_ptr);

    ~Entity();
private:
    void* game_ptr;
};

#endif
