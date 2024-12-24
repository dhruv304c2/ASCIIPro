#ifndef COMPONENT_H
#define COMPONENT_H

#include "../Core/Time.h"
#include "../Core/InputManager.h"
#include <functional>
#include <sstream>
#include <stdexcept>
#include <vector>

enum ComponentId{
    NONE,
    TRANSFORM,
    CANVAS,
};

class Component {
public:
    Component();
    virtual ~Component();
    virtual void update(Time *time, std::vector<Component*>, InputManager* input);
    std::vector<Component *> attached;
    std::vector<Component *> all;
    bool isAttached(Component* comp);

    template <typename T> bool hasAttached(){
        for(auto c : attached){
            if(dynamic_cast<T*>(c)) return true;
        }
        return false;
    }

    template <typename T> T* getAttached(){
        for(auto c : attached){
            if(auto converted = dynamic_cast<T*>(c)) return converted;
        }

        std::ostringstream oss;
        oss << "No component with id:" << typeid(T).name() << "attached to the component"; 
        throw std::runtime_error(oss.str());
    }
};

#endif
