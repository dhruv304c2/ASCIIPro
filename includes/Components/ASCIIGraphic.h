#ifndef ASCIIGRAPHICS_H
#define ASCIIGRAPHICS_H

#include <string>
#include <vector>
#include "../ECS/Component.h"
#include "Transform.h"

class ASCIIGraphic : public Component{
public:
    ASCIIGraphic();
    ~ASCIIGraphic();
    Vector2D center = Vector2D(0,0);
    int width();
    int height();
    virtual std::vector<std::vector<char>> ascii();
};

#endif
