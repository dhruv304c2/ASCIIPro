#include "Core/GameEvent.h"
#include <vector>

GameEvent::GameEvent() {}

GameEvent::~GameEvent() {}

void GameEvent::addListener(Listener listener) {
    listeners.push_back(listener);
}

void GameEvent::removeListener(Listener listener) {
    auto it = std::find_if(listeners.begin(), listeners.end(), [&listener](Listener const& l) {
        return &l == &listener;
    });

    if (it != listeners.end()) {
        listeners.erase(it);
    }
}

void GameEvent::removeAllListeners(){
    listeners.clear();
}

void GameEvent::trigger(){
    for(auto const& listener : listeners){
	listener();
    }
}
