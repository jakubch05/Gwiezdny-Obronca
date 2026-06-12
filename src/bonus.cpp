// Bonus.cpp
#include "bonus.h"

Bonus::Bonus(sf::Texture& texture, float x, float y)
    : GameObject(x, y)
{
    sprite.setTexture(texture);
    sprite.setScale(0.03f, 0.03f);

    velocity = sf::Vector2f(0.f, 150.f); // 150 px/s w dol
    rotationSpeed = 90.f;                 // 90 stopni/s - lekki obrot (animacja)

    // origin na srodku - obrot bedzie wokol centrum sprite'a
    sf::FloatRect b = sprite.getLocalBounds();
    sprite.setOrigin(b.width / 2.0f, b.height / 2.0f);

    syncVisual();
}

void Bonus::syncVisual() {
    sprite.setPosition(position);
    sprite.setRotation(rotation);
}

void Bonus::update(float deltaTime) {
    GameObject::update(deltaTime); // ruch + obrot + syncVisual()

    if (position.y > 770.f) {
        kill();
    }
}

void Bonus::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Bonus::getBounds() const {
    return sprite.getGlobalBounds();
}
