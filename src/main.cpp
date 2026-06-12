#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

// Twoje pliki nagłówkowe
#include "GameConfig.h"
#include "gameobject.h"
#include "player.h"
#include "enemy.h"
#include "laser.h"
#include "egg.h"
#include "bonus.h"
#include "hud.h"
#include "scoremanager.h"
#include "Menu.h"
#include "boss.h"

// Stany gry
enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

// Zmodyfikowana funkcja, która co 3 falę spawnuje Bossa zamiast zwykłych kurczaków
void spawnWave(std::vector<std::unique_ptr<GameObject>>& objects, sf::Texture& enemyTexture, int rows, int cols, int waveNum) {
    if (waveNum % 3 == 0) {
        // FALA BOSSA (30 HP)
        objects.push_back(std::make_unique<Boss>(enemyTexture, GameConfig::WINDOW_WIDTH / 2.0f, 150.0f, 30));
    } else {
        // ZWYKŁA FALA
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                objects.push_back(std::make_unique<Enemy>(enemyTexture, 100.0f + j * 80.0f, 50.0f + i * 80.0f));
            }
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    // Tworzenie okna
    sf::RenderWindow window(sf::VideoMode(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT), "Chicken Invaders Clone");
    window.setFramerateLimit(60);

    // Inicjalizacja podsystemów
    HUD hud;
    Menu menu(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT);
    ScoreManager scoreManager;

    // Główny kontener na obiekty
    std::vector<std::unique_ptr<GameObject>> objects;
    Player* playerPtr = nullptr;

    // Ładowanie tekstur
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("enemy3.png")) std::cerr << "Blad wczytywania: enemy3.png!" << std::endl;
    sf::Texture bonusTexture;
    if (!bonusTexture.loadFromFile("bonus.png")) std::cerr << "Blad wczytywania: bonus.png!" << std::endl;

    // Zmienne stanu gry
    int score = 0;
    int wave = 1;
    float enemySpeed = GameConfig::ENEMY_BASE_SPEED;
    float enemyDirection = 1.0f;
    bool scoreSaved = false;

    GameState currentState = GameState::MENU;

    // --- FUNKCJA DO WCZYTYWANIA GRY ---
    auto loadGameFunc = [&]() {
        std::ifstream loadFile("savegame.txt");
        if (loadFile.is_open()) {
            int loadedLives;
            loadFile >> score >> wave >> loadedLives >> enemySpeed >> enemyDirection;

            float px, py;
            loadFile >> px >> py;

            objects.clear();

            auto newPlayer = std::make_unique<Player>();
            playerPtr = newPlayer.get();
            playerPtr->setPosition(px, py);
            playerPtr->setLives(loadedLives);
            objects.push_back(std::move(newPlayer));

            std::string type;
            float ex, ey;
            while (loadFile >> type >> ex >> ey) {
                if (type == "ENEMY") {
                    objects.push_back(std::make_unique<Enemy>(enemyTexture, ex, ey));
                } else if (type == "BOSS") {
                    // Wczytanie Bossa (dajemy mu domyślnie 30 HP przy wczytaniu)
                    objects.push_back(std::make_unique<Boss>(enemyTexture, ex, ey, 30));
                }
            }
            loadFile.close();

            hud.setScore(score);
            hud.setLives(playerPtr->getLives());
            hud.setWave(wave);
            hud.showGameOver(false);
            scoreSaved = false;
            currentState = GameState::PLAYING;
            std::cout << "Wczytano gre!" << std::endl;
        } else {
            std::cout << "Brak pliku zapisu!" << std::endl;
        }
    };

    sf::Clock clock;

    // --- GŁÓWNA PĘTLA GRY ---
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // ESCAPE - powrót do menu lub wyjście
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                if (currentState == GameState::MENU) window.close();
                else currentState = GameState::MENU;
            }

            // --- MENU ---
            if (currentState == GameState::MENU) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) menu.moveUp();
                    if (event.key.code == sf::Keyboard::Down) menu.moveDown();

                    if (event.key.code == sf::Keyboard::Enter) {
                        int selected = menu.getPressedItem();
                        if (selected == 0) {
                            // NOWA GRA
                            score = 0;
                            wave = 1;
                            enemySpeed = GameConfig::ENEMY_BASE_SPEED;
                            enemyDirection = 1.0f;
                            scoreSaved = false;

                            objects.clear();
                            auto playerUnique = std::make_unique<Player>();
                            playerPtr = playerUnique.get();
                            playerPtr->setLives(GameConfig::PLAYER_LIVES);
                            objects.push_back(std::move(playerUnique));

                            spawnWave(objects, enemyTexture, GameConfig::ENEMY_ROWS, GameConfig::ENEMY_COLS, wave);

                            hud.setScore(score);
                            hud.setLives(playerPtr->getLives());
                            hud.setWave(wave);
                            hud.showGameOver(false);

                            currentState = GameState::PLAYING;
                        }
                        else if (selected == 1) {
                            // WCZYTAJ GRE
                            loadGameFunc();
                        }
                        else if (selected == 2) {
                            // WYJŚCIE
                            window.close();
                        }
                    }
                }
            }

            // --- KLAWISZE SZYBKIEGO ZAPISU (Tylko w trakcie gry) ---
            if (currentState == GameState::PLAYING) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
                    std::ofstream saveFile("savegame.txt");
                    if (saveFile.is_open()) {
                        saveFile << score << " " << wave << " " << playerPtr->getLives() << " " << enemySpeed << " " << enemyDirection << "\n";
                        saveFile << playerPtr->getPosition().x << " " << playerPtr->getPosition().y << "\n";

                        for (auto& obj : objects) {
                            if (auto* enemy = dynamic_cast<Enemy*>(obj.get())) {
                                if (enemy->isAlive()) saveFile << "ENEMY " << enemy->getPosition().x << " " << enemy->getPosition().y << "\n";
                            } else if (auto* boss = dynamic_cast<Boss*>(obj.get())) {
                                if (boss->isAlive()) saveFile << "BOSS " << boss->getPosition().x << " " << boss->getPosition().y << "\n";
                            }
                        }
                        saveFile.close();
                        std::cout << "Zapisano gre! (F5)" << std::endl;
                    }
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F9) {
                    loadGameFunc();
                }
            }

            // --- POWRÓT Z EKRANU ŚMIERCI ---
            if (currentState == GameState::GAME_OVER) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    currentState = GameState::MENU;
                }
            }
        }

        // ==============================================
        // --- AKTUALIZACJA LOGIKI (TYLKO PODCZAS GRY) ---
        // ==============================================
        if (currentState == GameState::PLAYING) {

            // 1. Ruch formacji kurczaków i Bossa
            for (auto& obj : objects) {
                if (auto* enemy = dynamic_cast<Enemy*>(obj.get())) {
                    enemy->setVelocity({enemySpeed * enemyDirection, 0.f});
                }
                // Boss sam steruje swoim ruchem w update(), więc pomijamy go tutaj
            }

            // 2. Aktualizacja wszystkich obiektów (Polimorfizm)
            for (auto& obj : objects) obj->update(deltaTime);

            std::vector<std::unique_ptr<GameObject>> newObjects;

            // 3. Strzał gracza
            if (auto laser = playerPtr->shoot()) newObjects.push_back(std::move(laser));

            // 4. Krawędzie ekranu i ataki (Jajka)
            bool edgeHit = false;
            for (auto& obj : objects) {
                // Zachowanie zwykłego kurczaka
                if (auto* enemy = dynamic_cast<Enemy*>(obj.get())) {
                    if (auto egg = enemy->tryDropEgg()) newObjects.push_back(std::move(egg));
                    sf::FloatRect b = enemy->getBounds();
                    if (b.left <= 0 || b.left + b.width >= GameConfig::WINDOW_WIDTH) edgeHit = true;
                }
                // Zachowanie Bossa
                else if (auto* boss = dynamic_cast<Boss*>(obj.get())) {
                    auto bossEggs = boss->dropSpreadEggs();
                    for (auto& e : bossEggs) newObjects.push_back(std::move(e));
                }
            }

            if (edgeHit) {
                enemyDirection *= -1.0f;
                for (auto& obj : objects) {
                    if (auto* enemy = dynamic_cast<Enemy*>(obj.get())) enemy->move({0.f, 30.f});
                }
            }

            // 5. System Kolizji
            for (auto& a : objects) {
                // Laser vs Przeciwnicy
                if (auto* laser = dynamic_cast<Laser*>(a.get())) {
                    for (auto& b : objects) {
                        // Sprawdzenie ze zwykłym wrogiem
                        if (auto* enemy = dynamic_cast<Enemy*>(b.get())) {
                            if (enemy->isAlive() && laser->getBounds().intersects(enemy->getBounds())) {
                                score += GameConfig::SCORE_PER_ENEMY;
                                if (rand() % 100 < 20) {
                                    newObjects.push_back(std::make_unique<Bonus>(bonusTexture, enemy->getPosition().x, enemy->getPosition().y));
                                }
                                enemy->kill();
                                laser->kill();
                                break;
                            }
                        }
                        // Sprawdzenie z Bossem
                        else if (auto* boss = dynamic_cast<Boss*>(b.get())) {
                            if (boss->isAlive() && laser->getBounds().intersects(boss->getBounds())) {
                                score += 20; // Punkty za samo trafienie w Bossa
                                laser->kill();

                                if (boss->takeDamage()) { // Jeśli boss zginął
                                    score += 1000;
                                    // Rozsypanie mnóstwa udek
                                    for(int k=0; k<5; k++) {
                                        newObjects.push_back(std::make_unique<Bonus>(bonusTexture, boss->getPosition().x - 40.f + (k*20.f), boss->getPosition().y));
                                    }
                                }
                                break;
                            }
                        }
                    }
                }

                // Jajko vs Gracz
                if (auto* egg = dynamic_cast<Egg*>(a.get())) {
                    if (egg->getBounds().intersects(playerPtr->getBounds())) {
                        playerPtr->hit();
                        egg->kill();
                    }
                }

                // Bonus vs Gracz
                if (auto* bonus = dynamic_cast<Bonus*>(a.get())) {
                    if (bonus->getBounds().intersects(playerPtr->getBounds())) {
                        score += GameConfig::SCORE_PER_BONUS;
                        bonus->kill();
                    }
                }
            }

            // 6. Przejście do następnej fali
            bool anyEnemyLeft = false;
            for (auto& obj : objects) {
                if (dynamic_cast<Enemy*>(obj.get()) && obj->isAlive()) anyEnemyLeft = true;
                if (dynamic_cast<Boss*>(obj.get()) && obj->isAlive()) anyEnemyLeft = true;
            }

            if (!anyEnemyLeft) {
                wave++;
                enemySpeed += 20.0f;
                enemyDirection = 1.0f;
                spawnWave(objects, enemyTexture, GameConfig::ENEMY_ROWS, GameConfig::ENEMY_COLS, wave);
                hud.setWave(wave);
            }

            // --- NOWOŚĆ: Sprawdzenie, czy kurczaki dotarły na dół (Inwazja) ---
            bool invasionSuccessful = false;
            for (auto& obj : objects) {
                if (auto* enemy = dynamic_cast<Enemy*>(obj.get())) {
                    // Sprawdzamy, czy dół kurczaka dotknął dolnej strefy ekranu
                    if (enemy->isAlive() && (enemy->getPosition().y + enemy->getBounds().height) >= (GameConfig::WINDOW_HEIGHT - 80.f)) {
                        invasionSuccessful = true;
                        break; // Wystarczy, że jeden dotrze na dół
                    }
                }
                else if (auto* boss = dynamic_cast<Boss*>(obj.get())) {
                    if (boss->isAlive() && (boss->getPosition().y + boss->getBounds().height) >= (GameConfig::WINDOW_HEIGHT - 80.f)) {
                        invasionSuccessful = true;
                        break;
                    }
                }
            }

            // 7. Koniec gry (Game Over) - teraz przegrywasz też, gdy inwazja się powiedzie
            if (playerPtr->getLives() <= 0 || invasionSuccessful) {
                currentState = GameState::GAME_OVER;
                hud.showGameOver(true);

                // Zapisujemy wynik jesli go jeszcze nie zapisano
                if (!scoreSaved) {
                    scoreManager.addScore("Gracz1", score);
                    hud.updateHighScoresDisplay(scoreManager.getScores());
                    scoreSaved = true;
                }
            }

            // 8. Zarządzanie pamięcią obiektów
            for (auto& n : newObjects) objects.push_back(std::move(n));

            objects.erase(
                std::remove_if(objects.begin(), objects.end(),
                               [](const std::unique_ptr<GameObject>& o) { return !o->isAlive(); }),
                objects.end()
                );

            // 9. Aktualizacja tekstów
            hud.setScore(score);
            hud.setLives(playerPtr->getLives());
        }

        // =================
        // --- RYSOWANIE ---
        // =================
        window.clear(sf::Color(10, 10, 40));

        if (currentState == GameState::MENU) {
            menu.draw(window);
        }
        else if (currentState == GameState::PLAYING) {
            for (auto& obj : objects) obj->draw(window);
            hud.draw(window);
        }
        else if (currentState == GameState::GAME_OVER) {
            for (auto& obj : objects) obj->draw(window);
            hud.draw(window);
        }

        window.display();
    }

    return 0;
}

