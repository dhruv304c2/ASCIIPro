#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include <functional>
#include <vector>

class GameEvent {
using Listener = std::function<void()>;
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
