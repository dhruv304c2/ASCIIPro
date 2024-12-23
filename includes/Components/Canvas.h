#ifndef CANVAS_H
#define CANVAS_H

#include "../ECS/Component.h"
#include "ASCIIGraphic.h"
#include "Transform.h"
#include <vector>

class Canvas : public Component {
public:
    Canvas();
    ~Canvas();
    void update(Time *time, std::vector<Component*> all) override;
private:
    Vector2D<int> clipPoint(Vector2D<int> point);
    void drawASCII(ASCIIGraphic& graphics);
    void clearCanvas();
    char canvas[50][100];
    const int MAX_X = 99;
    const int MAX_Y = 49;
};

#endif
