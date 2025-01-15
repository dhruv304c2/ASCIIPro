#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../ECS/Component.h"
#include "Math/Vector2D.h"

class Transform : public Component{
public:
    Transform(void* ent_ptr);
    ~Transform();
    Vector2D<float> position;
};

#endif
