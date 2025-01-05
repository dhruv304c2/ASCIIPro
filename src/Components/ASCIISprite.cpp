#include "Components/ASCIISprite.h"
#include "Components/ASCIIGraphic.h"
#include "Core/Sprite/SpriteExport.h"
#include <random>
#include <string>
#include <vector>

ASCIISprite::ASCIISprite(void* ent_ptr) : ASCIIGraphic(ent_ptr) {}

ASCIISprite::~ASCIISprite() {}

void ASCIISprite::useExport(SpriteExport& exported){
    sprite_mat = exported.sliced()[0];
}

void ASCIISprite::useRaw(std::string const& path){
    auto exported = SpriteExport(path);
    sprite_mat = exported.rawImage();
}

void ASCIISprite::use(std::string const& path, int const& slice){
    auto exported = SpriteExport(path);
    sprite_mat = exported.sliced()[slice];
}

std::vector<std::vector<wchar_t>> ASCIISprite::pixelMatrix(){
    return sprite();
}

std::vector<std::vector<wchar_t>> ASCIISprite::sprite(){
    return sprite_mat;
}

