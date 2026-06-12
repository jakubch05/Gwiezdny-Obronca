#pragma once
#include <SFML/Graphics.hpp>
#include "gameobject.h"

class Bonus : public GameObject {
private:
    sf::Sprite sprite;

protected:
    void syncVisual() override;

public:
    Bonus(sf::Texture& texture, float x, float y);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;
};
