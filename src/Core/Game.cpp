#include "Core/Input/InputManager.h"
#include "Core/Game.h"
#include <string>
#include <vector>

Game::Game() {
    _game_clock = GameClock();
    _game_clock.recordStartGameTime();
    _input = InputManager();
    _window = Window();
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

Window* Game::window(){
    return &_window;
}

void Game::run(){
    while(true){
	for(auto e : _entities){
	    auto time = _game_clock.time(); 
	    e ->update(time);
	}
	_input.getKeys();
	_game_clock.recordFrame();
    }
}
