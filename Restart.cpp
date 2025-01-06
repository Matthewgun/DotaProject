#include "restart.h"
#include <cstdlib> // Для std::system

Restart::Restart() {
    // Загрузка текстуры из файла
    if (!buttonTexture.loadFromFile("assets/restart1.png")) { // Укажите путь к вашему изображению
        throw std::runtime_error("Failed to load button texture");
    }

    // Создание спрайта из текстуры
    buttonSprite.setTexture(buttonTexture);
    buttonSprite.setPosition(70, 70); // Позиция кнопки на экране
    buttonSprite.setScale(0.25f, 0.25f);
}

void Restart::draw(sf::RenderWindow& window) {
    window.draw(buttonSprite); // Отрисовка спрайта кнопки
}

void Restart::handleMouseClick(const sf::Vector2f& mousePos) {
    if (isHovered(mousePos)) {
        // Перезапуск приложения
        std::system("start DotaProject.exe"); // Измените этот путь на путь к вашему исполняемому файлу
        std::exit(0); // Закрыть текущий экземпляр
    }
}

bool Restart::isHovered(const sf::Vector2f& mousePos) const {
    return buttonSprite.getGlobalBounds().contains(mousePos);
}
