#ifndef ASCIISPRITE_H
#define ASCIISPRITE_H

#include "ASCIIGraphic.h"
#include "../Core/Sprite/SpriteExport.h"
#include <string>
#include <vector>

class ASCIISprite : public ASCIIGraphic {
public:
    ASCIISprite(void* ent_ptr);
    ~ASCIISprite();
    void useExport(SpriteExport& exported);
    void useRaw(std::string const& path);
    void use(std::string const& path, int const& slice = 0);
    std::vector<std::vector<wchar_t>> sprite();
    std::vector<std::vector<wchar_t>> pixelMatrix() override;
protected:
    std::vector<std::vector<wchar_t>> sprite_mat;
};

#endif
