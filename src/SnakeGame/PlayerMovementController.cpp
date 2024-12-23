#include "../.././includes/SnakeGame/PlayerMovementController.h"

PlayerMovementController::PlayerMovementController() {}

PlayerMovementController::~PlayerMovementController() {}

void PlayerMovementController::update(Time* time, std::vector<Component*> all){
    Transform* transform = getAttached<Transform>();
    transform->position = transform -> position + speed;
    wrapPos();
}

void PlayerMovementController::wrapPos(){
    Transform* transform = getAttached<Transform>();
    Vector2D<float> pos = transform -> position;
    Vector2D<int> posInt = static_cast<Vector2D<int>>(pos);
    int x = posInt.x;
    int y = posInt.y;
    if(x > worldMaxX){
	x = worldMinX;
    }
    if(x < worldMinX){
	x = worldMinX;
    }
    if(y > worldMaxY){
	y = worldMinY;
    }
    if(y < worldMinY){
	y = worldMaxY;
    }
    transform -> position = Vector2D<float>((float)x,(float)y);
}

