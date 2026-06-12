// Player.cpp
#include "player.h"
#include <iostream>

Player::Player()
    : GameObject(0.f, 0.f),
    speed(400.f), fireRate(0.25f), fireCooldown(0.f),
    lives(3), invulnTimer(0.f)
{
    if (!texture.loadFromFile("player.png")) {
        std::cerr << "Blad: Nie udalo sie wczytac pliku player.png!" << std::endl;
    }
    if (!laserTexture.loadFromFile("laser.png")) {
        std::cerr << "Blad: Nie udalo sie wczytac pliku laser.png!" << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setScale(0.1f, 0.1f);

    // Startowa pozycja - na srodku, u dolu ekranu (1280x720)
    sf::FloatRect b = sprite.getGlobalBounds();
    position = sf::Vector2f(640.0f - b.width / 2.0f, 600.0f);
    syncVisual();
}

void Player::syncVisual() {
    sprite.setPosition(position);
}

void Player::update(float deltaTime) {
    // Predkosc liniowa (px/s) ustawiana na podstawie wcisnietych klawiszy
    velocity = sf::Vector2f(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocity.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocity.x += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)    || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) velocity.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)  || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) velocity.y += speed;

    GameObject::update(deltaTime); // position += velocity*dt, syncVisual()

    // Ograniczenia ekranu 1280x720
    sf::FloatRect bounds = sprite.getGlobalBounds();
    if (bounds.left < 0) position.x = 0;
    if (bounds.left + bounds.width > 1280) position.x = 1280 - bounds.width;
    if (bounds.top < 0) position.y = 0;
    if (bounds.top + bounds.height > 720) position.y = 720 - bounds.height;
    syncVisual();

    // Odliczanie cooldownu strzalu
    if (fireCooldown > 0.0f) fireCooldown -= deltaTime;

    // Miganie podczas niewrazliwosci po trafieniu
    if (invulnTimer > 0.0f) {
        invulnTimer -= deltaTime;
        int alpha = (static_cast<int>(invulnTimer * 10) % 2 == 0) ? 80 : 255;
        sprite.setColor(sf::Color(255, 255, 255, alpha));
    } else {
        sprite.setColor(sf::Color(255, 255, 255, 255));
    }
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

std::unique_ptr<Laser> Player::shoot() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fireCooldown <= 0.0f) {
        fireCooldown = fireRate;
        float startX = position.x + sprite.getGlobalBounds().width / 2.0f;
        float startY = position.y;
        return std::make_unique<Laser>(laserTexture, startX, startY);
    }
    return nullptr;
}

void Player::hit() {
    if (invulnTimer <= 0.0f) {
        lives--;
        invulnTimer = 1.5f;
    }
}

int Player::getLives() const {
    return lives;
}

void Player::setLives(int l) {
    lives = l;
}
