#include "HeroLoader.h"
#include <iostream>

HeroLoader::HeroLoader() : dragging(false), draggedSpriteIndex(-1) {
    sprites.resize(4); // Резервируем место для 4 героев
    selected.resize(4, std::vector<bool>(35, false)); // Инициализируем состояние выделения для каждого спрайта
}

bool HeroLoader::loadHeroTextures() {
    if (!texture1.loadFromFile("assets/heroes1.png") ||
        !texture2.loadFromFile("assets/heroes2.png") ||
        !texture3.loadFromFile("assets/heroes3.png") ||
        !texture4.loadFromFile("assets/heroes4.png")) {
        std::cerr << "Error loading one or more textures." << std::endl;
        return false; 
    }

    setupHeroSprites(texture1, sprites[0], 0);
    setupHeroSprites(texture2, sprites[1], 1);
    setupHeroSprites(texture3, sprites[2], 2);
    setupHeroSprites(texture4, sprites[3], 3);

    return true;
}

void HeroLoader::setupHeroSprites(const sf::Texture& texture, std::vector<sf::Sprite>& heroSprites, int heroIndex) {
    const int spriteWidth = texture.getSize().x / 5; // Ширина одного спрайта (5 столбцов)
    const int spriteHeight = texture.getSize().y / 7; // Высота одного спрайта (7 строк)

    const float horizontalOffset = 80 + (heroIndex * (5 * spriteWidth * 0.57f)); // Позиция по горизонтали

    for (int row = 0; row < 7; ++row) { // Проходим по строкам
        for (int col = 0; col < 5; ++col) { // Проходим по столбцам
            sf::IntRect rect(col * spriteWidth, row * spriteHeight, spriteWidth, spriteHeight);
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setTextureRect(rect);
            sprite.setScale(0.55f, 0.55f); // Масштабирование
            sprite.setPosition(horizontalOffset + (col * spriteWidth * 0.57f), 550 + (row * spriteHeight * 0.57f)); // Позиционирование
            heroSprites.push_back(sprite); // Добавляем спрайт в вектор
            
        }
    }
}

void HeroLoader::draw(sf::RenderWindow& window) {
    for (size_t j = 0; j < sprites.size(); ++j) { // Проходим по каждому набору спрайтов
        for (size_t i = 0; i < sprites[j].size(); ++i) {
            window.draw(sprites[j][i]); // Рисуем каждый спрайт

            if (selected[j][i]) { // Если спрайт выделен
                sf::RectangleShape outline;
                outline.setSize(sf::Vector2f(sprites[j][i].getGlobalBounds().width, sprites[j][i].getGlobalBounds().height)); // Устанавливаем размер обводки
                outline.setPosition(sprites[j][i].getPosition()); // Устанавливаем позицию обводки
                outline.setFillColor(sf::Color::Transparent); // Прозрачный фон
                outline.setOutlineColor(sf::Color::Red); // Цвет обводки
                outline.setOutlineThickness(2); // Толщина обводки
                
                window.draw(outline); // Рисуем обводку
            }
        }
    }
}

void HeroLoader::selectSprite(int heroIndex, int spriteIndex) {
    selected[heroIndex][spriteIndex] = true; // Устанавливаем состояние выделения на true
}

void HeroLoader::deselectSprite(int heroIndex, int spriteIndex) {
    selected[heroIndex][spriteIndex] = false; // Устанавливаем состояние выделения на false
}

void HeroLoader::handleMouseClick(const sf::Vector2f& mousePos) {
    for (int j = 0; j < 4; ++j) { 
        for (int i = 0; i < 35; ++i) { 
            auto& sprite = sprites[j][i]; 

            if (sprite.getGlobalBounds().contains(mousePos)) { 
                if (!dragging) {
                    if (!selected[j][i]) {
                    dragging = true;
                    draggedSpriteIndex = j * 35 + i; // Сохраняем индекс перетаскиваемого спрайта
                    
                    selectSprite(j, i); // Выделяем спрайт при нажатии
                    std::cout << "Герой из набора: " << j << ", номер героя: " << i << std::endl;
                    }
                }
            } else {
                deselectSprite(j, i); 
            }
        }
    }
}

void HeroLoader::updateDraggedSpritePosition(const sf::Vector2f& mousePos) {
    if (dragging && draggedSpriteIndex != -1) {
        int heroIndex = draggedSpriteIndex / 35;
        int spriteIndex = draggedSpriteIndex % 35;
        sprites[heroIndex][spriteIndex].setPosition(mousePos); // Обновляем позицию перетаскиваемого спрайта
    }
}

void HeroLoader::stopDragging() {
    dragging = false;
    draggedSpriteIndex = -1; // Сбрасываем индекс перетаскиваемого спрайта
}
