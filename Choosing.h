#ifndef CHOOSING_H
#define CHOOSING_H

#include <SFML/Graphics.hpp>
#include <vector>

class Choosing {
public:
    Choosing();
    void setupRectangles(); // Метод для настройки прямоугольников
    void draw(sf::RenderWindow& window); // Метод для рисования всех прямоугольников
    void selectRectangle(int index); // Метод для выделения прямоугольника
    void deselectRectangle(int index); // Метод для снятия выделения
    std::vector<sf::RectangleShape>& getRectangles() { return rectangles; } // Доступ к прямоугольникам
    void handleMouseClick(const sf::Vector2f& mousePos);
    bool isPointInsideAnyRectangle(const sf::Vector2f& point);
private:
    std::vector<sf::RectangleShape> rectangles; // Вектор для хранения прямоугольников
    std::vector<bool> selected; // Вектор для хранения состояния выделения
};

#endif // CHOOSING_H