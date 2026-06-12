// Laser.h
#pragma once
#include <SFML/Graphics.hpp>
#include "projectile.h"

// Pocisk gracza - leci w gore ze stala predkoscia.
class Laser : public Projectile {
private:
    sf::Sprite sprite;

protected:
    void syncVisual() override;

public:
    Laser(sf::Texture& texture, float startX, float startY);
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;
};


