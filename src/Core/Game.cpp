#include "Core/Input/InputManager.h"
#include "Core/Rendering/GameRenderer.h"
#include "Core/Rendering/ProfilerRenderer.h"
#include "Core/Rendering/Renderer.h"
#include "Core/Viewport/ViewportManager.h"
#include "Core/Game.h"
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

Game::Game() : 
    _window(), 
    _viewport_manager(&_window),
    _game_clock(),
    _input(),
    _profiler(&_game_clock){ 
    std::cout << "starting game session..." << std::endl;
    
    //Creating Ports
    auto game_node = _viewport_manager.root();
    std::cout<< "found root viewport node..." << std::endl;
    auto profiler_node = _viewport_manager.split(game_node,ViewportSplit::Horizontal,0.7);
    std::cout<< "profiler viewport created" << std::endl;
    auto log_viewport = _viewport_manager.split(profiler_node,ViewportSplit::Vertical,0.3);

    std::cout<< "created required viewports..." << std::endl;

    //Creating Renderers
    _game_renderer = new GameRenderer(game_node->item, this);
    _profiler_renderer = new ProfilerRenderer(profiler_node->item, this, &_profiler);
    _game_clock.recordStartGameTime();
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

ViewportRect Game::window(){
    return _game_renderer->viewport();
}

void Game::run(){
    std::cout<< "running game" << std::endl;
    for(auto const& e : _entities){
	e -> start();
    }

    _viewport_manager.start();

    while (true) {
	for(auto const& e : _entities){
	    auto time = _game_clock.time(); 
	    e ->update(time);
	}

	_profiler_renderer->update();
	_game_renderer->update();

	_viewport_manager.render();

	_input.getKeys();
	_game_clock.recordFrame();
	_window.update();
    }
}
