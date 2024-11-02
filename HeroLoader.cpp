// HeroLoader.cpp
#include "HeroLoader.h"
#include <iostream>

HeroLoader::HeroLoader() {}

bool HeroLoader::loadHero1() {
    if (!texture1.loadFromFile("assets/heroes1.png")) {
        std::cerr << "Error loading texture from file: assets/heroes1.png" << std::endl;
        return false; 
    }
    sprite1.setTexture(texture1);
    sprite1.setScale(0.57f, 0.57f);
    sprite1.setPosition(80, 550);
    return true;
}

bool HeroLoader::loadHero2() {
    if (!texture2.loadFromFile("assets/heroes2.png")) {
        std::cerr << "Error loading texture from file: assets/heroes2.png" << std::endl;
        return false; 
    }
    sprite2.setTexture(texture2);
    sprite2.setScale(0.57f, 0.57f);
    sprite2.setPosition(530, 550);
    return true;
}

bool HeroLoader::loadHero3() {
    if (!texture3.loadFromFile("assets/heroes3.png")) {
        std::cerr << "Error loading texture from file: assets/heroes3.png" << std::endl;
        return false; 
    }
    sprite3.setTexture(texture3);
    sprite3.setScale(0.57f, 0.57f);
    sprite3.setPosition(980, 550);
    return true;
}

bool HeroLoader::loadHero4() {
    if (!texture4.loadFromFile("assets/heroes4.png")) {
        std::cerr << "Error loading texture from file: assets/heroes4.png" << std::endl;
        return false; 
    }
    sprite4.setTexture(texture4);
    sprite4.setScale(0.57f, 0.57f);
    sprite4.setPosition(1430, 550);
    return true;
}

void HeroLoader::draw(sf::RenderWindow& window) {
    window.draw(sprite1); // Рисуем первый спрайт
    window.draw(sprite2); // Рисуем второй спрайт
    window.draw(sprite3); // Рисуем третий спрайт
    window.draw(sprite4); // Рисуем четвертый спрайт
}