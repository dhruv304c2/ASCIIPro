#ifndef CANVAS_H
#define CANVAS_H

#include "Core/Viewport/Viewport.h"
#include "Math/Vector2D.h"

class Game;

struct ViewportRect{
    Vector2D<int> origin;
    int width;
    int height;
};

class Renderer {
public:
    Renderer(Viewport* view_port, Game* game);
    ~Renderer();
    void update();
    ViewportRect viewport();
protected:
    virtual void render();
    Vector2D<int> clipPoint(Vector2D<int> const& point);
    Viewport* _viewport;
    Game* _game;
    int _width = 0;
    int _height = 0;
    wchar_t** _canvas;
};

#endif
