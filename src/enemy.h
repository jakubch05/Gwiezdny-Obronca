#pragma once
#include "gameobject.h"
#include "egg.h"
#include <memory>

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

    std::unique_ptr<Egg> tryDropEgg() const;
};
