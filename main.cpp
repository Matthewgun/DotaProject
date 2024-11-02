#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "HeroLoader.h"

int main() {
     // Получаем разрешение рабочего стола
     sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

     // Создаем окно в полноэкранном режиме
     sf::RenderWindow window(desktopMode, "My Fullscreen Window", sf::Style::Fullscreen);

     // Создаем экземпляр HeroLoader
     HeroLoader heroLoader;

     // Загружаем героев отдельно
     if (!heroLoader.loadHero1() || 
         !heroLoader.loadHero2() || 
         !heroLoader.loadHero3() || 
         !heroLoader.loadHero4()) {
         return -1; // Завершаем программу при ошибке загрузки
     }

     // Основной цикл программы, который будет работать, пока окно открыто
     while (window.isOpen()) {
         sf::Event event;

         while (window.pollEvent(event)) {
             if (event.type == sf::Event::Closed) {
                 window.close();
             }
         }

         window.clear(sf::Color(50, 50, 50)); // Очищаем окно темным серым цветом

         // Рисуем всех героев
         heroLoader.draw(window);

         window.display(); // Отображаем содержимое окна
     }

     return 0;
}