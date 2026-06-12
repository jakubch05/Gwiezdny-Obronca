#pragma once
#include "gameobject.h"
#include "egg.h"
#include <memory>
#include <vector>

class Boss : public GameObject {
private:
    sf::Sprite sprite;
    int hp;               // Punkty zycia Bossa
    float hitTimer;       // Zegar do animacji otrzymania obrazen
    float animationTime;  // Czas do plynnej animacji pulsowania

protected:
    void syncVisual() override;

public:
    Boss(sf::Texture& texture, float x, float y, int health);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;

    // Boss traci zycie i miga na czerwono. Zwraca true jesli zginął.
    bool takeDamage();

    // Rzuca kilka jajek jednoczesnie
    std::vector<std::unique_ptr<Egg>> dropSpreadEggs() const;
};
