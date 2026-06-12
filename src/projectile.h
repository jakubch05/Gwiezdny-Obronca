// Projectile.h
#pragma once
#include <SFML/Graphics.hpp>
#include "gameobject.h"

// Wspolna baza dla pociskow gracza (Laser) i wroga (Egg).
// Oba lecialy prostoliniowo i znikaja po wylocie za ekran.
class Projectile : public GameObject {
public:
    Projectile(float x, float y, sf::Vector2f velocity);

    // Przesuwa pocisk (GameObject::update) i sprawdza czy wylecial za ekran.
    void update(float deltaTime) override;


};
