#ifndef PLAYERMOVEMENTCONTROLLER_H
#define PLAYERMOVEMENTCONTROLLER_H

#include "../ECS/Component.h"
#include "../Components/Transform.h"
#include <vector>

class PlayerMovementController : public Component{
public:
    PlayerMovementController();
    ~PlayerMovementController();
    int worldMinX = 0;
    int worldMaxX = 99;
    int worldMinY = 0;
    int worldMaxY = 49;
    Vector2D<float> speed = Vector2D<float>(1,0);
    void update(Time* time, std::vector<Component*> all) override;
private:
    void wrapPos();
};

#endif
