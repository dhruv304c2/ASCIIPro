#include "../.././includes/ECS/Entity.h"
#include <string>
#include <type_traits>
#include <iostream>

Entity::Entity(std::string name) {
    this ->name = name;
}

template <typename T>
T* Entity::addComponent(){
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
    

    Component* component = T();
    components.push_back(component);
    return component;
}

template<typename T>
void Entity::removeComponent(){
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        auto it = std::remove_if(components.begin(), components.end(), [](Component* component) {
            if (dynamic_cast<T*>(component)) {
                delete component; 
                return true;
            }
            return false;
        });

        components.erase(it, components.end());
}

Entity::~Entity() {
    for(auto c : components){
	delete c;
    }
    components.clear();
}

