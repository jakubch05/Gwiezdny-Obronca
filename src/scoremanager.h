#pragma once
#include <vector>
#include <string>

// Struktura przechowujaca pojedynczy wynik
struct ScoreEntry {
    std::string name;
    int score;
};

class ScoreManager {
private:
    std::vector<ScoreEntry> highScores;
    std::string filename;
    int maxScores; // Ile wynikow trzymamy (np. TOP 5)

public:
    ScoreManager(const std::string& file = "scores.txt", int max = 5);

    void loadScores();
    void saveScores() const;
    void addScore(const std::string& playerName, int score);

    const std::vector<ScoreEntry>& getScores() const;
};
