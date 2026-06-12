#pragma once
#include <SFML/Graphics.hpp>
#include "gameobject.h"

class Projectile : public GameObject {
public:
    Projectile(float x, float y, sf::Vector2f velocity);
    void update(float deltaTime) override;


};
