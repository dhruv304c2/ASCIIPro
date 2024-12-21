#ifndef CANVAS_H
#define CANVAS_H

#include "../ECS/Component.h"
#include <vector>

class Canvas : public Component {
public:
    Canvas();
    ~Canvas();
    void update(Time *time) override;
private:
    char canvas[50][100];
    const int MAX_X = 99;
    const int MAX_Y = 49;
};

#endif
