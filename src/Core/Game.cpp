#include "Core/Input/InputManager.h"
#include "Core/Game.h"
#include <string>
#include <vector>

Game::Game(float delta) {
    time = new Time();
    time ->setDelta(delta);
    input = new InputManager();
}

Game::~Game() {
    delete time;
    delete input;
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
    Entity* ent = new Entity(name, (void*)this);
    entities.push_back(ent);
    return ent;
}

void Game::run(){
    while(true){
	input -> getKeys();
	for(auto e : entities){
	    e ->update(time, input);
	}
	time ->waitDelta();
    }
}
