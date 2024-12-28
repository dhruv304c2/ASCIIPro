#include "Core/Input/InputManager.h"
#include <iostream>
#include <unordered_map>

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#elif __APPLE__
#include <ApplicationServices/ApplicationServices.h>
#endif

InputManager::InputManager() {
    int begin = static_cast<int>(Key::None);
    int end = static_cast<int>(Key::End);

    for(int i = begin; i < end; ++i) {
	Key key = static_cast<Key>(i);
	key_state_map[key] = Idle;
    }
}

InputManager::~InputManager() {}

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

bool InputManager::getKeyStateAsync(Key key) {
    int platformKeyCode = getPlatformKeyCode(key);
    if (platformKeyCode == -1) {
	std::cerr << "Key not supported on this platform.\n";
        return false;
    }

#ifdef _WIN32
    return GetAsyncKeyState(platformKeyCode) & 0x8000;
#elif __linux__
    Display* display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Failed to open X display.\n";
        return false;
    }

    char keyStates[32];
    XQueryKeymap(display, keyStates);

    KeyCode kc = static_cast<KeyCode>(platformKeyCode);
    bool isPressed = keyStates[kc / 8] & (1 << (kc % 8));

    XCloseDisplay(display);
    return isPressed;
#elif __APPLE__
    CGEventSourceRef eventSource = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);
    if (!eventSource) {
        std::cerr << "Failed to create event source.\n";
        return false;
    }

    bool isPressed = CGEventSourceKeyState(eventSource, platformKeyCode);
    CFRelease(eventSource);
    return isPressed;
#else
    std::cerr << "Unsupported platform.\n";
    return false;
#endif
}

int InputManager::getPlatformKeyCode(Key key) {
#ifdef _WIN32
    static const std::unordered_map<Key, int> keyMap = {
        { Key::A, 'A' },
        { Key::W, 'W' },
        { Key::S, 'S' },
        { Key::D, 'D' },
    };
#elif __linux__
    static const std::unordered_map<Key, int> keyMap = {
        { Key::A, XK_A },
        { Key::W, XK_W },
        { Key::S, XK_S },
        { Key::D, XK_D },
    };
#elif __APPLE__
    static const std::unordered_map<Key, int> keyMap = {
        { Key::A, 0 },
        { Key::W, 13 },
        { Key::S, 1 },
        { Key::D, 2 },
    };
#else
    static const std::unordered_map<Key, int> keyMap = {};
#endif

    auto it = keyMap.find(key);
    if (it != keyMap.end()) {
        return it->second;
    }

    return -1; 
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
