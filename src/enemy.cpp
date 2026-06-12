// Enemy.cpp
#include "enemy.h"
#include <cstdlib>

Enemy::Enemy(sf::Texture& texture, float x, float y)
    : GameObject(x, y)
{
    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f);
    syncVisual();
}

void Enemy::syncVisual() {
    sprite.setPosition(position);
}

void Enemy::update(float deltaTime) {
    // velocity.x jest ustawiane z zewnatrz przez formacje w main.cpp
    GameObject::update(deltaTime);
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Enemy::getBounds() const {
    return sprite.getGlobalBounds();
}

std::unique_ptr<Egg> Enemy::tryDropEgg() const {
    // ~1 jajko na sekunde na cala 48-osobowa formacje przy 60 FPS
    if (rand() % 3000 == 0) {
        sf::FloatRect b = getBounds();
        return std::make_unique<Egg>(position.x + b.width / 2.0f, position.y + b.height);
    }
    return nullptr;
}
