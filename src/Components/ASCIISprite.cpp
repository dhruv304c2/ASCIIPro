#include "Components/ASCIISprite.h"
#include "Components/ASCIIGraphic.h"
#include <vector>

ASCIISprite::ASCIISprite(void* ent_ptr) : ASCIIGraphic(ent_ptr) {}

ASCIISprite::~ASCIISprite() {}

void ASCIISprite::useExport(SpriteExport &exported){
    sprite_mat = exported.sliced()[0];
}

std::vector<std::vector<wchar_t>> ASCIISprite::pixelMatrix(){
    return sprite();
}

std::vector<std::vector<wchar_t>> ASCIISprite::sprite(){
    return sprite_mat;
}

