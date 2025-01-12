#ifndef HEROLOADER_H
#define HEROLOADER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
//#include "Spriteinfo.h"
#include "Choosing.h"
#include <fstream>
#include <vector>
#include <string>
class HeroLoader {
public:
    HeroLoader();
    bool loadHeroTextures(); // Метод для загрузки всех текстур героев
    void draw(sf::RenderWindow& window); // Метод для рисования всех спрайтов
    std::vector<sf::Sprite>& getSprites(int heroIndex) { return sprites[heroIndex]; } // Доступ к спрайтам
    void selectSprite(int heroIndex, int spriteIndex); // Метод для выделения спрайта
    void deselectSprite(int heroIndex, int spriteIndex); // Метод для снятия выделения
    void saveFilteredHeroes();
    void handleMouseClick(const sf::Vector2f& mousePos);
    void updateDraggedSpritePosition(const sf::Vector2f& mousePos);
    void stopDragging();
private:
    void setupHeroSprites(const sf::Texture& texture, std::vector<sf::Sprite>& sprites, int heroIndex); // Метод для настройки спрайтов героев
    //SpriteInfo spriteInfo;
    bool loadHeroNames(); // Метод для загрузки имен героев
    sf::Texture texture1, texture2, texture3, texture4; // Текстуры
    std::vector<std::vector<sf::Sprite>> sprites; // Вектор векторов для хранения спрайтов каждого героя
    std::vector<std::vector<bool>> selected; // Вектор векторов для хранения состояния выделения спрайтов
    std::vector<std::string> heroList; // Вектор для хранения имен героев
     bool dragging; // Для отслеживания состояния перетаскивания
    int draggedSpriteIndex; // Индекс текущего перетаскиваемого спрайта
};

#endif // HEROLOADER_H