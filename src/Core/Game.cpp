#include "../.././includes/Core/Game.h"
#include <string>

Game::Game(Time* time, float delta) {
    time ->setDelta(delta);
    this -> time = time;
}

Game::~Game() {
    delete time;
    for(auto e : entities){
	delete e;
    };
    entities.clear();
}

Entity* Game::createEntity(std::string name){
    Entity* ent = new Entity(name);
    entities.push_back(ent);
    return ent;
}

void Game::run(){
    while(true){
	for(auto e : entities){
	    e ->update(time);
	}
	time ->waitDelta();
    }
}
