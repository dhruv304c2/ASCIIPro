#include "../.././includes/Core/GameLoop.h"

GameLoop::GameLoop(Time* time) {
    this -> time = time;
}

GameLoop::~GameLoop() {
    delete time;
}

void GameLoop::update(){
   time ->waitDelta(); 
}
