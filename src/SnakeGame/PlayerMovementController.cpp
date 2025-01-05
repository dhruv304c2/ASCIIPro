#include "SnakeGame/PlayerMovementController.h"
#include "ECS/Component.h"

PlayerMovementController::PlayerMovementController(void* ent_ptr) : Component(ent_ptr) {}

PlayerMovementController::~PlayerMovementController() {}

void PlayerMovementController::update(Time& time,
    InputManager* input){

    handleInputs(input);
    Transform* transform = getAttached<Transform>();
    Vector2D<float> movement = dir * speed * time.delta();
    transform->position = transform -> position + movement;
    wrapPos();
}

void PlayerMovementController::handleInputs(InputManager* input){
    if(input -> isKeyDown(W)){
	dir = Vector2D<float>(0,-1);
    }
    if(input -> isKeyDown(S)){
	dir = Vector2D<float>(0,1);
    }
    if(input -> isKeyDown(A)){
	dir = Vector2D<float>(-1,0);
    }
    if(input -> isKeyDown(D)){
	dir = Vector2D<float>(1,0);
    }
}

void PlayerMovementController::wrapPos(){
    Transform* transform = getAttached<Transform>();
    Vector2D<float> pos = transform -> position;
    float x = pos.x;
    float y = pos.y;
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
    transform -> position = Vector2D<float>(x,y);
}

