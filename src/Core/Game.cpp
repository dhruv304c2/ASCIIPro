#include "Core/Input/InputManager.h"
#include "Core/Game.h"
#include <iostream>
#include <string>
#include <vector>

Game::Game() {
    game_clock = GameClock();
    game_clock.recordStartGameTime();

    input = new InputManager();
}

Game::~Game() {
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
	    auto time = game_clock.time(); 
	    e ->update(time, input);
	}

	std::cout << "Time delta: " << game_clock.time().delta() << std::endl;
	game_clock.recordFrame();
    }
}
