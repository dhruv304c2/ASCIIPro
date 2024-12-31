#ifndef ASCIISPRITE_H
#define ASCIISPRITE_H

#include "ASCIIGraphic.h"
#include "../Core/Sprite/SpriteExport.h"
#include <vector>

class ASCIISprite : public ASCIIGraphic {
public:
    ASCIISprite(void* ent_ptr);
    ~ASCIISprite();
    void useExport(SpriteExport &exported);
    std::vector<std::vector<wchar_t>> sprite();
    std::vector<std::vector<wchar_t>> pixelMatrix() override;
protected:
    std::vector<std::vector<wchar_t>> sprite_mat;
};

#endif
