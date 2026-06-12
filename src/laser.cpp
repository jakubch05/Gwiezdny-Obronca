#include "laser.h"

Laser::Laser(sf::Texture& texture, float startX, float startY)
    : Projectile(startX, startY, sf::Vector2f(0.f, -600.f))
{
    sprite.setTexture(texture);
    sprite.setScale(0.05f, 0.05f);

    position.x -= sprite.getGlobalBounds().width / 2.0f;
    syncVisual();
}

void Laser::syncVisual() {
    sprite.setPosition(position);
}

void Laser::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Laser::getBounds() const {
    return sprite.getGlobalBounds();
}
