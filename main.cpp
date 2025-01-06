#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "HeroLoader.h"
#include "Choosing.h"
#include "Restart.h"

int main() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "My Fullscreen Window", sf::Style::Fullscreen);

    HeroLoader heroLoader;
    Choosing choosing;
    Restart restartButton;


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

                    heroLoader.handleMouseClick(mousePos); 
                    choosing.handleMouseClick(mousePos);
                    restartButton.handleMouseClick(mousePos);
                }
            }

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                heroLoader.updateDraggedSpritePosition(mousePos); 
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    heroLoader.stopDragging(); 

                    // Проверка на попадание в прямоугольники при отпускании кнопки мыши.
                    if(choosing.isPointInsideAnyRectangle(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){  
                        // Здесь можно добавить логику обработки успешного перетаскивания.
                    }  
                }
            }
        }

        window.clear(sf::Color(50, 50, 50)); 


        choosing.draw(window); 
        heroLoader.draw(window);
        restartButton.draw(window);

        window.display(); 
    }

    return 0;
}