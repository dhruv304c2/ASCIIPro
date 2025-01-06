#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include <vector>

using Listener = void(*)();

class GameEvent {
public:
    GameEvent();
    ~GameEvent();
    void addListener(Listener listener);
    void removeListener(Listener listener);
    void removeAllListeners();
    void trigger();
private:
    std::vector<Listener> listeners;
};

#endif
