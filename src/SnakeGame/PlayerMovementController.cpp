#include "SnakeGame/PlayerMovementController.h"
#include "ECS/Component.h"

PlayerMovementController::PlayerMovementController(void* ent_ptr) : Component(ent_ptr) {}

PlayerMovementController::~PlayerMovementController() {}

void PlayerMovementController::update(Time* time,
    InputManager* input){

    handleInputs(input);
    Transform* transform = getAttached<Transform>();
    transform->position = transform -> position + speed;
    wrapPos();
}

void PlayerMovementController::handleInputs(InputManager* input){
    if(input -> isKeyDown(W)){
	speed = Vector2D<float>(0,-1);
    }
    if(input -> isKeyDown(S)){
	speed = Vector2D<float>(0,1);
    }
    if(input -> isKeyDown(A)){
	speed = Vector2D<float>(-1,0);
    }
    if(input -> isKeyDown(D)){
	speed = Vector2D<float>(1,0);
    }
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
	x = worldMaxX;
    }
    if(y > worldMaxY){
	y = worldMinY;
    }
    if(y < worldMinY){
	y = worldMaxY;
    }
    transform -> position = Vector2D<float>((float)x,(float)y);
}

