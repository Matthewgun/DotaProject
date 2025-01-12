#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "HeroLoader.h"
#include "Choosing.h"
#include "Restart.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp> // Библиотека JSON (https://github.com/nlohmann/json)

using json = nlohmann::json;

// Структура для представления матчапа
struct Matchup {
    std::string hero;
    double disadvantage;
};

// Загрузка списка противников из HeroList.txt
std::vector<std::string> loadOpponents(const std::string& filename) {
    std::vector<std::string> opponents;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return opponents;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            opponents.push_back(line);
        }
    }
    file.close();
    return opponents;
}

// Загрузка данных о матчапах из HeroList.json
json loadMatchups(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return json();
    }
    json data;
    file >> data;
    file.close();
    return data;
}

std::vector<std::pair<std::string, double>> findBestHeroes(const std::vector<std::string>& opponents, const json& matchups, int topN = 5) {
    std::vector<std::pair<std::string, double>> heroScores;

    for (auto& [hero, matchupData] : matchups.items()) {
        // Пропускаем героя, если он уже в списке противников
        if (std::find(opponents.begin(), opponents.end(), hero) != opponents.end()) {
            continue;
        }

        double totalDisadvantage = 0.0;

        for (const auto& opponent : opponents) {
            bool found = false;

            // Ищем героя среди худших матчапов
            for (const auto& matchup : matchupData["worst_matchups"]) {
                if (matchup["hero"].get<std::string>() == opponent) {
                    totalDisadvantage += matchup["disadvantage"].get<double>();
                    found = true;
                    break;
                }
            }

            // Если герой не найден среди худших матчапов, ищем среди лучших
            if (!found) {
                for (const auto& matchup : matchupData["best_matchups"]) {
                    if (matchup["hero"].get<std::string>() == opponent) {
                        totalDisadvantage += matchup["disadvantage"].get<double>();
                        break;
                    }
                }
            }
        }

        // Добавляем героя и его общий "дизадвантаж" в список
        heroScores.emplace_back(hero, totalDisadvantage);
    }

    // Сортируем список героев по возрастанию "дизадвантажа"
    std::sort(heroScores.begin(), heroScores.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    // Возвращаем топ N героев
    if (heroScores.size() > topN) {
        heroScores.resize(topN);
    }
    return heroScores;
}


int main() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "Dota2 Picker", sf::Style::Fullscreen);

    HeroLoader heroLoader;
    Choosing choosing;
    Restart restartButton;
    bool heroesDisplayed = false; // Флаг для предотвращения повторного вывода

    if (!heroLoader.loadHeroTextures()) {
        return -1; 
    }

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { 
        std::cerr << "Ошибка: не удалось загрузить шрифт!" << std::endl;
        return -1;
    }

    sf::Text resultText;
    resultText.setFont(font);
    resultText.setCharacterSize(30);
    resultText.setFillColor(sf::Color::Green);
    resultText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 4.0f); // Центрирование текста


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
                            // Загрузка данных
                    std::vector<std::string> opponents = loadOpponents("HeroList.txt");

                    if (opponents.size() == 4 && !heroesDisplayed) {
                        json matchups = loadMatchups("HeroList.json");
                        if (opponents.empty() || matchups.empty()) {
                            std::cerr << "Ошибка: данные не загружены!" << std::endl;
                            return 1;
                        }

                        // Поиск 5 лучших героев
                        auto bestHeroes = findBestHeroes(opponents, matchups, 5);

                        if (!bestHeroes.empty()) {
                            std::string displayText;
                            for (const auto& [hero, score] : bestHeroes) {
                                displayText += hero + "\n";
                            }
                            resultText.setString(displayText);
                            sf::FloatRect textRect = resultText.getLocalBounds();
                            resultText.setOrigin(textRect.width / 2, textRect.height / 2);
                            resultText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 4.0f);
                            heroesDisplayed = true;
                        }  
                    }

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
        window.draw(resultText);
        window.display(); 
    }

    return 0;
}