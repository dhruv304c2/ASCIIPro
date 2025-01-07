#ifndef CANVAS_H
#define CANVAS_H

#include "../ECS/Component.h"
#include "ASCIIGraphic.h"
#include "Transform.h"

class Canvas : public Component {
public:
    Canvas(void* ent_ptr);
    ~Canvas();
    void resizeCanvas(int const& width, int const& height);
    void start() override;
    void update() override;
private:
    Vector2D<int> clipPoint(Vector2D<int> const& point, 
            int const& canvas_width, 
            int const& canvas_height);
    void drawASCII(ASCIIGraphic& graphics);
    void clearCanvas();
    wchar_t** canvas;
    int width();
    int height();
    int _width = 1000;
    int _height = 500;
};

#endif
