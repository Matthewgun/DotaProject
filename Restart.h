#ifndef RESTART_H
#define RESTART_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Restart {
public:
    Restart();
    void draw(sf::RenderWindow& window);
    void handleMouseClick(const sf::Vector2f& mousePos);
    bool isHovered(const sf::Vector2f& mousePos) const;

private:
    sf::Texture buttonTexture; // Текстура для кнопки
    sf::Sprite buttonSprite;   // Спрайт для отображения текстуры
};

#endif // RESTART_H
