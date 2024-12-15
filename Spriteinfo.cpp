// SpriteInfo.cpp
#include "SpriteInfo.h"

void SpriteInfo::addSprite(const sf::Texture& texture, int index) {
    SpriteData data = { texture, index };
    sprites.push_back(data);
}

const std::vector<SpriteInfo::SpriteData>& SpriteInfo::getSprites() const {
    return sprites;
}

void SpriteInfo::printSpriteInfo(int index) const {
    if (index >= 0 && index < sprites.size()) {
        std::cout << "Sprite Index: " << sprites[index].index << std::endl;
        std::cout << "Texture Address: " << &sprites[index].texture << std::endl;
    } else {
        std::cout << "Invalid sprite index: " << index << std::endl;
    }
}
