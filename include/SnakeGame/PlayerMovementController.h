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
    Vector2D<float> speed = Vector2D<float>(1,0);
    void update(Time* time, InputManager* input) override;
private:
    void wrapPos();
    void handleInputs(InputManager* input);
};

#endif
