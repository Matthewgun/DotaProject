#include "Choosing.h"

Choosing::Choosing() {
    setupRectangles(); // Set up rectangles when object is created
}

void Choosing::setupRectangles() {
    const int numRectangles = 10; // 2 пары по 5 штук
    const float width = 100.0f;
    const float height = 50.0f;
    
    rectangles.resize(numRectangles);
    selected.resize(numRectangles, false);

    // Позиционирование: 5 слева и 5 справа
    for (int i = 0; i < numRectangles; ++i) {
        rectangles[i].setSize(sf::Vector2f(width, height));
        rectangles[i].setFillColor(sf::Color::Green);

        if (i < 5) { // Первые 5 прямоугольников слева
            rectangles[i].setPosition(200 + i * (width + 10), 300); // Слева
        } else { // Остальные 5 прямоугольников справа
            rectangles[i].setPosition(1100 + (i - 5) * (width + 10), 300); // Справа
        }
    }
}

void Choosing::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < rectangles.size(); ++i) {
        if (selected[i]) {
            rectangles[i].setOutlineColor(sf::Color::Red);
            rectangles[i].setOutlineThickness(2);
        } else {
            rectangles[i].setOutlineThickness(0);
        }
        window.draw(rectangles[i]); // Draw each rectangle
    }
}

void Choosing::selectRectangle(int index) {
    if (index >= 0 && index < selected.size()) {
        selected[index] = true; // Set selection state to true
    }
}

void Choosing::deselectRectangle(int index) {
    if (index >= 0 && index < selected.size()) {
        selected[index] = false; // Set selection state to false
    }
}

bool Choosing::isPointInsideAnyRectangle(const sf::Vector2f& point) {
   for (const auto& rectangle : rectangles) {
       if (rectangle.getGlobalBounds().contains(point)) {
           return true; 
       }
   }
   return false; 
}

void Choosing::handleMouseClick(const sf::Vector2f& mousePos) {
    for (int i = 0; i < rectangles.size(); ++i) { 
        if (rectangles[i].getGlobalBounds().contains(mousePos)) {
            selectRectangle(i); // Выделяем прямоугольник при нажатии
        } else {
            deselectRectangle(i); // Снимаем выделение с других прямоугольников
        }
    }
}