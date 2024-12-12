#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "HeroLoader.h"
#include "Choosing.h"

int main() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "My Fullscreen Window", sf::Style::Fullscreen);

    HeroLoader heroLoader;
    Choosing choosing;

    if (!heroLoader.loadHeroTextures()) {
        return -1; 
    }

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) { 
                if (event.mouseButton.button == sf::Mouse::Left) { 
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window)); 

                    heroLoader.handleMouseClick(mousePos); // Обработка клика по спрайтам
                    choosing.handleMouseClick(mousePos); // Обработка клика по прямоугольникам
                }
            }
        }

        window.clear(sf::Color(50, 50, 50)); 

        heroLoader.draw(window);
        choosing.draw(window); // Рисуем все прямоугольники

        window.display(); 
    }

    return 0;
}
