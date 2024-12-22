#include "../.././includes/Core/Game.h"
#include <string>
#include <vector>

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

std::vector<Component*> Game::allComponents() {
    std::vector<Component*> all;
    for(auto e : entities){
	all.insert(all.end(),e->components.begin(), e->components.end());
    }
    return all;
}

Entity* Game::createEntity(std::string name){
    Entity* ent = new Entity(name);
    entities.push_back(ent);
    return ent;
}

void Game::run(){
    while(true){
	for(auto e : entities){
	    e ->update(time, allComponents());
	}
	time ->waitDelta();
    }
}
