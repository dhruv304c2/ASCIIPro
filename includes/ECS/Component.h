#ifndef COMPONENT_H
#define COMPONENT_H

#include "../Core/Time.h"
#include <functional>
#include <vector>

enum ComponentId{
    NONE,
    CANVAS
};

class Component {
public:
  Component(ComponentId id = NONE);
  virtual ~Component();
  virtual void update(Time *time);
  ComponentId compId();
  std::vector<Component *> attached;
protected:
    const ComponentId id;
};

#endif
