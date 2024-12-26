#ifndef ASCIISPRITE_H
#define ASCIISPRITE_H

#include "ASCIIGraphic.h"
#include "../Core/Sprite/SpriteExport.h"
#include <vector>

class ASCIISprite : public ASCIIGraphic{
public:
    ASCIISprite();
    ~ASCIISprite();
    void useExport(SpriteExport &exported);
    std::vector<std::vector<char>> sprite();
    std::vector<std::vector<char>> ascii() override;
protected:
    std::vector<std::vector<char>> sprite_mat;
};

#endif
