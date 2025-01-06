#ifndef WINDOW_H
#define WINDOW_H

#include "Core/GameEvent.h"

class Window {
public:
    Window();
    ~Window();
    void update();
    int width();
    int height();
    GameEvent on_window_resize;
private:
    int _prev_width;
    int _prev_height;
};
#endif
