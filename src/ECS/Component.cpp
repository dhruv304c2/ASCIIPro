#include "../.././includes/ECS/Component.h"

Component::Component(ComponentId compId) : id(compId) {}
ComponentId Component::compId(){
    return id;
}
Component::~Component() {}
void Component::update(Time* time){};
