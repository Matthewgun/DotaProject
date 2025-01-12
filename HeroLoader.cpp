#include "HeroLoader.h"
#include <iostream>

HeroLoader::HeroLoader() : dragging(false), draggedSpriteIndex(-1) {
    sprites.resize(4); // Резервируем место для 4 героев
    selected.resize(4, std::vector<bool>(35, false)); // Инициализируем состояние выделения для каждого спрайта

        // Очищаем содержимое файла HeroList.txt при запуске
    std::ofstream heroFile("HeroList.txt", std::ios::trunc);
    if (!heroFile.is_open()) {  
        std::cerr << "Ошибка: не удалось открыть файл HeroList.txt для очистки!" << std::endl;
    }
    heroFile.close();

     // Загружаем имена героев
    if (!loadHeroNames()) {
        std::cerr << "Failed to load hero names!" << std::endl;
    }
}

bool HeroLoader::loadHeroNames() {
    std::ifstream inFile("AllHeroList.txt");  // Открываем файл с именами героев
    if (!inFile) {
        std::cerr << "Не удалось открыть файл AllHeroList.txt" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        heroList.push_back(line);  // Добавляем каждое имя в вектор
    }

    inFile.close();
        // Печатаем количество считанных имен
    std::cout << "Loaded " << heroList.size() << " hero names." << std::endl;
    return true;
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
     static int selectedCount = 0;
    std::ofstream heroFile("HeroList.txt", std::ios::app); // Режим "append" для добавления в файл
    if (!heroFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл HeroList.txt для записи!" << std::endl;
        return;
    }
    for (int j = 0; j < 4; ++j) { 
        for (int i = 0; i < 35; ++i) { 
            auto& sprite = sprites[j][i]; 

            if (sprite.getGlobalBounds().contains(mousePos)) { 
                // Если спрайт не выделен и нет другого выделенного спрайта
                if (!selected[j][i] && !dragging) {
                    // Снимаем выделение с других спрайтов
                    for (int k = 0; k < 4; ++k) {
                        for (int l = 0; l < 35; ++l) {
                            deselectSprite(k, l);
                        }
                    }
                    // Выделяем текущий спрайт
                    selectSprite(j, i);
                    dragging = false; // Перетаскивание не начинается сразу
                    draggedSpriteIndex = j * 35 + i; // Сохраняем индекс выделенного спрайта
                    int index;
                    // Вывод отладочной информации
                    if (j == 0)
                        index = i;
                    else if (j == 1)
                        index = 32 + i;
                    else if (j == 2) 
                        index = 63 + i;
                    else
                        index = 94 + i;
                    std::cout << heroList[index] << std::endl;
                    
                    if ((selectedCount / 2) % 2 == 1)
                        heroFile << heroList[index] << std::endl; // Записываем имя героя в файл
                    selectedCount++;
                    // Вызов парсера после записи 8-го героя
                    if (selectedCount == 8) {
                        std::cout << "Запущен парсер для анализа матчапов!" << std::endl;
                        
                    }

                } else if (selected[j][i]) {
                    // Если спрайт уже выделен, начинаем перетаскивание
                    dragging = true;
                    draggedSpriteIndex = j * 35 + i; // Сохраняем индекс перетаскиваемого спрайта
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