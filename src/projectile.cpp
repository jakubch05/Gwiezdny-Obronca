#include "projectile.h"

Projectile::Projectile(float x, float y, sf::Vector2f velocity)
    : GameObject(x, y)
{
    this->velocity = velocity;
}

void Projectile::update(float deltaTime) {
    GameObject::update(deltaTime);

    if (position.y < -50.f || position.y > 770.f) {
        kill();
    }
}
