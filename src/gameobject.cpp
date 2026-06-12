#include "gameobject.h"

GameObject::GameObject(float x, float y)
    : position(x, y), velocity(0.f, 0.f), rotation(0.f), rotationSpeed(0.f), alive(true)
{

}
void GameObject::update(float deltaTime) {
    position += velocity * deltaTime;
    rotation += rotationSpeed * deltaTime;
    syncVisual();
}

void GameObject::move(sf::Vector2f offset) {
    position += offset;
    syncVisual();
}

void GameObject::setVelocity(sf::Vector2f v) {
    velocity = v;
}

sf::Vector2f GameObject::getVelocity() const {
    return velocity;
}

sf::Vector2f GameObject::getPosition() const {
    return position;
}

bool GameObject::isAlive() const {
    return alive;
}

void GameObject::kill() {
    alive = false;
}

void GameObject::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
    syncVisual(); // Od razu aktualizujemy pozycję na ekranie
}
