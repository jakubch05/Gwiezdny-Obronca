#pragma once
#include "gameobject.h"
#include "egg.h"
#include <memory>
#include <vector>

class Boss : public GameObject {
private:
    sf::Sprite sprite;
    int hp;
    float hitTimer;
    float animationTime;

protected:
    void syncVisual() override;

public:
    Boss(sf::Texture& texture, float x, float y, int health);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;

    bool takeDamage();

    std::vector<std::unique_ptr<Egg>> dropSpreadEggs() const;
};
