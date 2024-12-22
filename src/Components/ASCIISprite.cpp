#include "../.././includes/Components/ASCIISprite.h"
#include <vector>

ASCIISprite::ASCIISprite() {
    sprite = {};
}

ASCIISprite::~ASCIISprite() {}

std::vector<std::vector<char>> ASCIISprite::ascii(){
    return sprite;
}

