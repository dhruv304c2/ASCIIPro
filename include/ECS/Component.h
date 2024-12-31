#ifndef COMPONENT_H
#define COMPONENT_H

#include "Core/Time.h"
#include "Core/Input/InputManager.h"
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
    Component(void* ent_ptr);

    virtual ~Component();

    virtual void update(Time *time , InputManager* input);

    virtual void update(Time *time);

    virtual void update();

    bool isAttached(Component* comp);


    template <typename T> bool hasAttached(){
        for(auto c : attached()){
            if(dynamic_cast<T*>(c)) return true;
        }
        return false;
    }

    template <typename T> T* getAttached(){
        for(auto c : attached()){
            if(auto converted = dynamic_cast<T*>(c)) return converted;
        }
        std::ostringstream oss;
        oss << "No component with id:" << typeid(T).name() << "attached to the component"; 
        throw std::runtime_error(oss.str());
    }

protected:
    void attachToEnt(void* ent_ptr);

    void* entity_ptr;

    void* game_ptr;

    std::vector<Component*> attached();

    std::vector<Component*> all();

    template<typename T> 
    std::vector<T*> all(){
        auto all = this -> all();
        std::vector<T*> requested;
        for(Component* comp : all){
            auto converted = dynamic_cast<T*>(comp);
            if(converted){
                requested.push_back(converted);
            }
        }
        return requested;
    }
};

#endif
