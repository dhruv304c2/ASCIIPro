#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <map>

enum Key{
    None,
    W,
    A,
    S,
    D,
    End 
};

enum KeyState{
    Idle,
    Pressed,
    Held,
    Released
};

static std::map<Key, int> KEY_MAPS = {
    {W, 0x57},
    {A, 0x41},
    {S, 0x53},
    {D, 0x44}
};


class InputManager {
public:
    InputManager();
    ~InputManager();
    void getKeys();
    bool getKeyStateAsync(Key key);
    int getPlatformKeyCode(Key key);
    bool isKey(Key key);
    bool isKeyUp(Key key);
    bool isKeyDown(Key key);
private:
    std::map<Key, KeyState> key_state_map;
};

#endif
