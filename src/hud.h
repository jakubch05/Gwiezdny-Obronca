#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "scoremanager.h"

class HUD {
private:
    sf::Font font;
    sf::Text scoreText;
    sf::Text livesText;
    sf::Text waveText;
    sf::Text gameOverText;
    bool gameOver;

    sf::Text highScoreTitle;
    std::vector<sf::Text> highScoreTexts;
public:
    HUD();
    void setScore(int score);
    void setLives(int lives);
    void setWave(int wave);
    void showGameOver(bool show);

    void updateHighScoresDisplay(const std::vector<ScoreEntry>& scores);
    void draw(sf::RenderWindow& window);
};
