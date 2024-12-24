#include "../.././includes/Core/InputManager.h"
#include <iostream>
#include <windows.h>
#include <winuser.h>

InputManager::InputManager() {
    int begin = static_cast<int>(Key::None);
    int end = static_cast<int>(Key::End);

    for(int i = begin; i < end; ++i) {
	Key key = static_cast<Key>(i);
	key_state_map[key] = Idle;
    }
}

InputManager::~InputManager() {
}

KeyState handleKeyDown(KeyState current){
    switch (current) {
	case Pressed:
	    return Held;
	case Held:
	    return Held;
	default:
	    return Pressed;
    }
}

KeyState handleKeyRelease(KeyState current){
    switch (current) {
	case Pressed:
	    return Released;
	case Held:
	    return Released;
	default:
	    return Idle;
    }
}

void InputManager::getKeys(){
    int begin = static_cast<int>(Key::None);
    int end = static_cast<int>(Key::End);

    for(int i = begin; i < end; ++i) {
	Key key = static_cast<Key>(i);
	char keyCode = KEY_MAPS[key];
	if(GetAsyncKeyState(keyCode) & 0x8000){
	    key_state_map[key] = handleKeyDown(key_state_map[key]); 
	}else{
	    key_state_map[key] = handleKeyRelease(key_state_map[key]);
	}
    }
}

bool InputManager::isKeyDown(Key key){
    return key_state_map[key] == Pressed;
}

bool InputManager::isKey(Key key){
    return key_state_map[key] == Pressed ||
	key_state_map[key] == Held;
}

bool InputManager::isKeyUp(Key key){
    return key_state_map[key] == Released;
}




