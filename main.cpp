#include <SFML/Window.hpp>

int main() {
    // Создаем окно с заданным размером и заголовком
    sf::Window window(sf::VideoMode(800, 600), "My window");

    // Основной цикл программы, который будет работать, пока окно открыто
    while (window.isOpen()) {
        sf::Event event;
        
        // Обрабатываем все события окна
        while (window.pollEvent(event)) {
            // Если событие закрытия окна, то закрываем его
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    return 0;
}