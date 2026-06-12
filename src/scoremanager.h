#pragma once
#include <vector>
#include <string>

struct ScoreEntry {
    std::string name;
    int score;
};

class ScoreManager {
private:
    std::vector<ScoreEntry> highScores;
    std::string filename;
    int maxScores;

public:
    ScoreManager(const std::string& file = "scores.txt", int max = 5);

    void loadScores();
    void saveScores() const;
    void addScore(const std::string& playerName, int score);

    const std::vector<ScoreEntry>& getScores() const;
};
