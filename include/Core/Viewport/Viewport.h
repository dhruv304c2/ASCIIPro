#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Core/GameEvent.h"
#include "Math/Vector2D.h"

class Viewport {
public:
    Viewport(int const& width, int const& height, Vector2D<int> const& origin);
    ~Viewport();
    void resize(int const& width,int const& height);
    Vector2D<int> origin();
    Vector2D<int> topRight();
    Vector2D<int> bottomLeft();
    Vector2D<int> bottomRight();
    int width();
    int height();
    GameEvent on_resize;
    void writeToBuffer(wchar_t** buffer, int const& width, int const& height);
    void writeToViewportBuffer(wchar_t** buffer, int const& width, int const& height);
    void clearViewportBuffer();
    wchar_t** buffer;
private:
    int m_width;
    int m_height;
    Vector2D<int> m_origin;
};

#endif
