#pragma once
#include "gameobject.h"
#include "laser.h"
#include <memory>

class Player : public GameObject {
private:
    sf::Texture texture;
    sf::Texture laserTexture;
    sf::Sprite sprite;

    float speed;
    float fireRate;
    float fireCooldown;

    int lives;
    float invulnTimer;

protected:
    void syncVisual() override;

public:
    Player();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;
    std::unique_ptr<Laser> shoot();

    void hit();
    int getLives() const;
    void setLives(int l);
};
