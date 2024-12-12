#ifndef HEROLOADER_H
#define HEROLOADER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class HeroLoader {
public:
    HeroLoader();
    bool loadHeroTextures(); // Метод для загрузки всех текстур героев
    void draw(sf::RenderWindow& window); // Метод для рисования всех спрайтов
    std::vector<sf::Sprite>& getSprites(int heroIndex) { return sprites[heroIndex]; } // Доступ к спрайтам
    void selectSprite(int heroIndex, int spriteIndex); // Метод для выделения спрайта
    void deselectSprite(int heroIndex, int spriteIndex); // Метод для снятия выделения
    void handleMouseClick(const sf::Vector2f& mousePos);
private:
    void setupHeroSprites(const sf::Texture& texture, std::vector<sf::Sprite>& sprites, int heroIndex); // Метод для настройки спрайтов героев

    sf::Texture texture1, texture2, texture3, texture4; // Текстуры
    std::vector<std::vector<sf::Sprite>> sprites; // Вектор векторов для хранения спрайтов каждого героя
    std::vector<std::vector<bool>> selected; // Вектор векторов для хранения состояния выделения спрайтов
};

#endif // HEROLOADER_H
