// Enemy.h
#pragma once
#include "gameobject.h"
#include "egg.h"
#include <memory>

// Kurczak - wrog. Ruch w formacji jest kontrolowany z zewnatrz przez setVelocity()
// (ustawiane przez main.cpp na podstawie wspolnego kierunku calej fali).
class Enemy : public GameObject {
private:
    sf::Sprite sprite;

protected:
    void syncVisual() override;

public:
    Enemy(sf::Texture& texture, float x, float y);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;

    // Z mala losowa szansa zwraca nowe jajko do zrzucenia, inaczej nullptr.
    std::unique_ptr<Egg> tryDropEgg() const;
};
