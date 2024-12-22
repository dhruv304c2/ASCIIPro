#ifndef ASCIISPRITE_H
#define ASCIISPRITE_H

#include "ASCIIGraphic.h"
#include <vector>

class ASCIISprite : public ASCIIGraphic{
public:
    ASCIISprite();
    ~ASCIISprite();
    std::vector<std::vector<char>> sprite;
    std::vector<std::vector<char>> ascii() override;
};

#endif
