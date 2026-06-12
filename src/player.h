// Player.h
#pragma once
#include "gameobject.h"
#include "laser.h"
#include <memory>

// Statek gracza - sterowanie klawiatura, strzelanie, zycia.
class Player : public GameObject {
private:
    sf::Texture texture;
    sf::Texture laserTexture;
    sf::Sprite sprite;

    float speed;        // predkosc ruchu w px/s
    float fireRate;      // czas (s) miedzy strzalami
    float fireCooldown;  // odliczanie do nastepnego strzalu

    int lives;
    float invulnTimer;   // czas (s) niewrazliwosci po trafieniu

protected:
    void syncVisual() override;

public:
    Player();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;

    // Jesli gracz strzela i cooldown minal, zwraca nowy Laser, inaczej nullptr.
    std::unique_ptr<Laser> shoot();

    void hit();          // odbiera 1 zycie (jesli nie jest niewrazliwy)
    int getLives() const;
    void setLives(int l);
};
