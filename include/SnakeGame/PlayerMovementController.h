#ifndef PLAYERMOVEMENTCONTROLLER_H
#define PLAYERMOVEMENTCONTROLLER_H

#include "../ECS/Component.h"
#include "../Components/Transform.h"

class PlayerMovementController : public Component{
public:
    PlayerMovementController(void* ent_ptr);
    ~PlayerMovementController();
    int worldMinX = 0;
    int worldMaxX = 99;
    int worldMinY = 0;
    int worldMaxY = 49;
    float speed = 10;
    Vector2D<float> dir = Vector2D<float>(1,0);
    void update(Time& time) override;
private:
    void wrapPos();
    void handleInputs(InputManager* input);
};

#endif
