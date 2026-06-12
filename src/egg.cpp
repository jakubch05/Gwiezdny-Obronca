// Egg.cpp
#include "egg.h"

Egg::Egg(float x, float y)
    : Projectile(x, y, sf::Vector2f(0.f, 250.f)) // 250 px/s w dol
{
    shape.setRadius(8.f);
    shape.setFillColor(sf::Color(255, 240, 200));
    shape.setOutlineColor(sf::Color(180, 150, 110));
    shape.setOutlineThickness(1.f);
    shape.setOrigin(8.f, 8.f);

    rotationSpeed = 180.f; // obrot 180 stopni/s podczas spadania (animacja)

    syncVisual();
}

void Egg::syncVisual() {
    shape.setPosition(position);
    shape.setRotation(rotation);
}

void Egg::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::FloatRect Egg::getBounds() const {
    return shape.getGlobalBounds();
}
