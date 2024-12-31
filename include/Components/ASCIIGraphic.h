#ifndef ASCIIGRAPHICS_H
#define ASCIIGRAPHICS_H

#include <vector>
#include "ECS/Component.h"
#include "Transform.h"

class ASCIIGraphic : public Component {
public:
    ASCIIGraphic(void* ent_ptr);
    ~ASCIIGraphic();
    Vector2D<int> center = Vector2D<int>(0,0);
    int width();
    int height();
    virtual std::vector<std::vector<wchar_t>> pixelMatrix();
    void debugPrint();
};

#endif
