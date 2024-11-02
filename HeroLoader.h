// HeroLoader.h
#ifndef HEROLOADER_H
#define HEROLOADER_H

#include <SFML/Graphics.hpp>
#include <string>

class HeroLoader {
public:
    HeroLoader();
    bool loadHero1();
    bool loadHero2();
    bool loadHero3();
    bool loadHero4();
    void draw(sf::RenderWindow& window); // Метод для рисования всех спрайтов

private:
    sf::Texture texture1, texture2, texture3, texture4; // Текстуры
    sf::Sprite sprite1, sprite2, sprite3, sprite4; // Спрайты
};

#endif // HEROLOADER_H