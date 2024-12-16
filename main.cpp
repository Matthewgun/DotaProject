#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <nlohmann/json.hpp>

using json = nlohmann::json; // Используем алиас для удобства

struct HeroMatchup {
    std::string hero;
    double disadvantage;
};

class Dota2Picker {
public:
    Dota2Picker(const std::string& jsonFilePath) {
        loadHeroData(jsonFilePath);
    }

    void run() {
        std::vector<std::string> radiantHeroes;
        std::vector<std::string> direHeroes;

        // Запрос стороны игры
        std::string side;
        std::cout << "Выберите сторону (Dire или Radiant): ";
        std::cin >> side;

        // Ввод героев для команды Radiant или Dire
        if (side == "Radiant") {
            int radiantCount = getHeroInput(radiantHeroes, "Radiant");

            // Если введено 4 героя, автоматически переходим к Dire
            if (radiantCount == 4) {
                std::cout << "Переход к команде Dire...\n";
                getHeroInput(direHeroes, "Dire");
            } else if (radiantCount > 0) {
                // Если введено 2 героя, запрашиваем переход к Dire
                std::string command;
                while (true) {
                    std::cout << "Введите 'go_dire' для перехода к Dire: ";
                    std::cin >> command;

                    if (command == "go_dire") {
                        break; // Выходим из цикла, если команда введена правильно
                    } else {
                        std::cout << "Неверная команда. Попробуйте снова.\n";
                    }
                }

                getHeroInput(direHeroes, "Dire");
            }
        } else if (side == "Dire") {
            int direCount = getHeroInput(direHeroes, "Dire");

            // Если введено 4 героя, автоматически переходим к Radiant
            if (direCount == 4) {
                std::cout << "Переход к команде Radiant...\n";
                getHeroInput(radiantHeroes, "Radiant");
            } else if (direCount > 0) {
                // Если введено 2 героя, запрашиваем переход к Radiant
                std::string command;
                while (true) {
                    std::cout << "Введите 'go_radiant' для перехода к Radiant: ";
                    std::cin >> command;

                    if (command == "go_radiant") {
                        break; // Выходим из цикла, если команда введена правильно
                    } else {
                        std::cout << "Неверная команда. Попробуйте снова.\n";
                    }
                }

                getHeroInput(radiantHeroes, "Radiant");
            }
        } else {
            std::cout << "Неверная сторона. Пожалуйста, перезапустите программу и выберите 'Dire' или 'Radiant'.\n";
            return;
        }

        // Предложение пиков
        if (!radiantHeroes.empty() || !direHeroes.empty()) {
            std::cout << "Введите 'Suggest peaks' для предложения пиков: ";
            std::string command;
            std::cin.ignore(); // Игнорируем остаток строки
            std::getline(std::cin, command); // Читаем всю строку

            if (command == "Suggest peaks") {
                suggestHeroes(radiantHeroes, direHeroes, side);
            } else {
                std::cout << "Неверная команда.\n";
            }
        }
    }

private:
    std::map<std::string, std::vector<HeroMatchup>> heroData;

    void loadHeroData(const std::string& jsonFilePath) {
        std::ifstream file(jsonFilePath);
        if (!file.is_open()) {
            std::cerr << "Не удалось открыть файл: " << jsonFilePath << "\n";
            return;
        }

        json root;
        file >> root;

        for (const auto& hero : root.items()) { // Используем items() для итерации по объекту
            const auto& heroName = hero.key();
            for (const auto& matchup : hero.value()["best_matchups"]) {
                HeroMatchup hm{matchup["hero"], matchup["disadvantage"]};
                heroData[heroName].push_back(hm);
            }
        }
    }

    int getHeroInput(std::vector<std::string>& heroes, const std::string& team) {
        int heroCount;

        while (true) {
            std::cout << "Введите количество героев для команды " << team << " (2 или 4): ";
            std::cin >> heroCount;

            if (heroCount == 2 || heroCount == 4) break; // Проверяем корректность ввода

            std::cout << "Пожалуйста, введите 2 или 4.\n";
        }

        for (int i = 0; i < heroCount; ++i) {
            std::string hero;
            std::cout << "Введите имя героя: ";
            std::cin >> hero;
            heroes.push_back(hero);
        }

        return heroCount; // Возвращаем количество введенных героев
    }

    void suggestHeroes(const std::vector<std::string>& radiantHeroes, const std::vector<std::string>& direHeroes, const std::string& playerSide) {
        std::vector<HeroMatchup> suggestions;

        if (playerSide == "Radiant") {
            // Предлагаем лучших героев против Dire
            for (const auto& hero : direHeroes) {
                if (heroData.find(hero) != heroData.end()) {
                    const auto& bestMatchups = heroData[hero];
                    suggestions.insert(suggestions.end(), bestMatchups.begin(), bestMatchups.end());
                } else {
                    std::cout << "Герой " << hero << " не найден.\n";
                    return;
                }
            }
        } else { // playerSide == "Dire"
            // Предлагаем лучших героев против Radiant
            for (const auto& hero : radiantHeroes) {
                if (heroData.find(hero) != heroData.end()) {
                    const auto& bestMatchups = heroData[hero];
                    suggestions.insert(suggestions.end(), bestMatchups.begin(), bestMatchups.end());
                } else {
                    std::cout << "Герой " << hero << " не найден.\n";
                    return;
                }
            }
        }

        // Удаляем дубликаты и тех героев, которые уже выбраны
        suggestions.erase(std::remove_if(suggestions.begin(), suggestions.end(), [&](const HeroMatchup& suggestion) {
            return std::find(radiantHeroes.begin(), radiantHeroes.end(), suggestion.hero) != radiantHeroes.end() ||
                   std::find(direHeroes.begin(), direHeroes.end(), suggestion.hero) != direHeroes.end();
        }), suggestions.end());

        // Сортируем предложения по disadvantage
        std::sort(suggestions.begin(), suggestions.end(), [](const HeroMatchup& a, const HeroMatchup& b) {
            return a.disadvantage < b.disadvantage; // Чем меньше disadvantage, тем лучше
        });

        // Печатаем топ-5 предложения
        std::cout << "Рекомендуемые герои:\n";
        for (size_t i = 0; i < 5 && i < suggestions.size(); ++i) {
            std::cout << suggestions[i].hero << " с disadvantage: " << suggestions[i].disadvantage << "\n";
        }
    }
};

int main() {
    Dota2Picker picker("HeroList.json");
    picker.run();
    return 0;
}
