// Bonus.h
#pragma once
#include <SFML/Graphics.hpp>
#include "gameobject.h"

// Bonus (udko) spadajace po zestrzeleniu kurczaka. Obraca sie podczas opadania.
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
