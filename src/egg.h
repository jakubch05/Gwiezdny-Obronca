// Egg.h
#pragma once
#include <SFML/Graphics.hpp>
#include "projectile.h"

// Jajko zrzucane przez kurczaki - leci w dol i obraca sie podczas spadania.
class Egg : public Projectile {
private:
    sf::CircleShape shape;

protected:
    void syncVisual() override;

public:
    Egg(float x, float y);

    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;
};
