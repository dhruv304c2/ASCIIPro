#include "Components/ASCIISprite.h"
#include <vector>

ASCIISprite::ASCIISprite() {}

ASCIISprite::~ASCIISprite() {}

void ASCIISprite::useExport(SpriteExport &exported){
    sprite_mat = exported.sliced()[0];
}

std::vector<std::vector<char>> ASCIISprite::ascii(){
    return sprite();
}

std::vector<std::vector<char>> ASCIISprite::sprite(){
    return sprite_mat;
}

