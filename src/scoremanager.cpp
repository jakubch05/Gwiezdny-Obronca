#include "scoremanager.h"
#include <fstream>
#include <algorithm>
#include <iostream>

ScoreManager::ScoreManager(const std::string& file, int max)
    : filename(file), maxScores(max)
{
    loadScores();
}

void ScoreManager::loadScores() {
    highScores.clear();
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string name;
        int score;
        // Wczytujemy pary (Imie Wynik) dopoki nie skoncza sie w pliku
        while (file >> name >> score) {
            highScores.push_back({name, score});
        }
        file.close();
    } else {
        // Jesli plik nie istnieje, tworzymy puste wpisy
        for(int i=0; i<maxScores; i++) {
            highScores.push_back({"---", 0});
        }
    }
}

void ScoreManager::saveScores() const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& entry : highScores) {
            file << entry.name << " " << entry.score << "\n";
        }
        file.close();
    } else {
        std::cerr << "Blad: Nie mozna zapisac do pliku " << filename << std::endl;
    }
}

void ScoreManager::addScore(const std::string& playerName, int score) {
    // Dodajemy nowy wynik na koniec listy
    highScores.push_back({playerName, score});

    // Sortujemy malejaco (od najwiekszego do najmniejszego wyniku)
    std::sort(highScores.begin(), highScores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
    });

    // Jesli lista jest dluzsza niz dozwolona liczba wpisow, ucinamy ja
    if (highScores.size() > static_cast<size_t>(maxScores)) {
        highScores.resize(maxScores);
    }

    // Zapisujemy nowy ranking do pliku
    saveScores();
}

const std::vector<ScoreEntry>& ScoreManager::getScores() const {
    return highScores;
}
