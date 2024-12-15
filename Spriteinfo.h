// SpriteInfo.h
#ifndef SPRITEINFO_H
#define SPRITEINFO_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream> // Include for std::cout

class SpriteInfo {
public:
    struct SpriteData {
        sf::Texture texture;
        int index;
    };

    void addSprite(const sf::Texture& texture, int index);
    const std::vector<SpriteData>& getSprites() const;

    // New method to print sprite info
    void printSpriteInfo(int index) const;

private:
    std::vector<SpriteData> sprites; // Vector to hold sprite data
};

#endif // SPRITEINFO_H
