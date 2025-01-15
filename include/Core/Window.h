#ifndef WINDOW_H
#define WINDOW_H

#include "Core/GameEvent.h"
#include "Core/Viewport/Viewport.h"
#include "Math/Vector2D.h"

class Window {
public:
    Window();
    ~Window();
    void update();
    int width();
    int height();
    GameEvent on_window_resize;
    Vector2D<int> originScreenCoord();
private:
    Vector2D<int> _origin_screen_coord;
    int _prev_width;
    int _prev_height;
};
#endif
