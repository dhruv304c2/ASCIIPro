#include "Core/Input/InputManager.h"
#include "Core/Game.h"
#include <iostream>
#include <string>
#include <vector>

Game::Game() {
    _game_clock = GameClock();
    _game_clock.recordStartGameTime();
    _input = InputManager();
}

Game::~Game() {
    for(auto e : _entities){
	delete e;
    };
    _entities.clear();
}

std::vector<Component*> Game::allComponents() {
    std::vector<Component*> all;
    for(auto e : _entities){
	all.insert(all.end(),e->components.begin(), e->components.end());
    }
    return all;
}

Entity* Game::createEntity(std::string name){
    Entity* ent = new Entity(name, (void*)this);
    _entities.push_back(ent);
    return ent;
}

InputManager* Game::input(){
    return &_input;
}

void Game::run(){
    while(true){
	_input.getKeys();
	for(auto e : _entities){
	    auto time = _game_clock.time(); 
	    e ->update(time);
	}

	std::cout << "Time delta: " << _game_clock.time().delta() << std::endl;
	_game_clock.recordFrame();
    }
}
