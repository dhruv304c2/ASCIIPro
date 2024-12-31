#ifndef CANVAS_H
#define CANVAS_H

#include "../ECS/Component.h"
#include "ASCIIGraphic.h"
#include "Transform.h"

class Canvas : public Component {
public:
    Canvas(void* ent_ptr);
    ~Canvas();
    void update() override;
private:
    Vector2D<int> clipPoint(Vector2D<int> point);
    void drawASCII(ASCIIGraphic& graphics);
    void clearCanvas();
    wchar_t canvas[50][100];
    const int MAX_X = 99;
    const int MAX_Y = 49;
};

#endif
