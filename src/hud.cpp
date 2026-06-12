#include "hud.h"
#include <iostream>
#include <string>
#include "scoremanager.h"

HUD::HUD() : gameOver(false) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Blad: Nie udalo sie wczytac pliku arial.ttf!" << std::endl;
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(28);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(20.f, 15.f);
    scoreText.setString("Wynik: 0");

    livesText.setFont(font);
    livesText.setCharacterSize(28);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(20.f, 50.f);
    livesText.setString("Zycia: 3");

    waveText.setFont(font);
    waveText.setCharacterSize(28);
    waveText.setFillColor(sf::Color::White);
    waveText.setPosition(20.f, 85.f);
    waveText.setString("Fala: 1");

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(64);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    sf::FloatRect b = gameOverText.getLocalBounds();
    gameOverText.setOrigin(b.width / 2.0f, b.height / 2.0f);
    gameOverText.setPosition(640.f, 360.f); // środek okna 1280x720

    highScoreTitle.setFont(font);
    highScoreTitle.setCharacterSize(40);
    highScoreTitle.setFillColor(sf::Color::Yellow);
    highScoreTitle.setString("TOP 5 WYNIKOW:");
    sf::FloatRect b2 = highScoreTitle.getLocalBounds();
    highScoreTitle.setOrigin(b2.width / 2.0f, b2.height / 2.0f);
    highScoreTitle.setPosition(640.f, 400.f); // Pod napisem Game Over
}

void HUD::setScore(int score) {
    scoreText.setString("Wynik: " + std::to_string(score));
}

void HUD::setLives(int lives) {
    livesText.setString("Zycia: " + std::to_string(lives));
}

void HUD::setWave(int wave) {
    waveText.setString("Fala: " + std::to_string(wave));
}

void HUD::showGameOver(bool show) {
    gameOver = show;
}

void HUD::updateHighScoresDisplay(const std::vector<ScoreEntry>& scores) {
    highScoreTexts.clear();
    float startY = 500.f;
    for (size_t i = 0; i < scores.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setString(std::to_string(i + 1) + ". " + scores[i].name + " - " + std::to_string(scores[i].score));

        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        text.setPosition(640.f, startY + i * 40.f);

        highScoreTexts.push_back(text);
    }
}

void HUD::draw(sf::RenderWindow& window) {
    if (gameOver) {
        window.draw(gameOverText);
        window.draw(highScoreTitle);
        for (const auto& txt : highScoreTexts) {
            window.draw(txt);
        }
    } else {
        window.draw(scoreText);
        window.draw(livesText);
        window.draw(waveText);
    }
}
