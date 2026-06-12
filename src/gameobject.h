#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
protected:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float rotation;
    float rotationSpeed;
    bool alive;

    virtual void syncVisual() {}

public:
    GameObject(float x = 0.f, float y = 0.f);
    virtual ~GameObject() = default;
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow& window) const = 0;

    virtual sf::FloatRect getBounds() const = 0;

    void move(sf::Vector2f offset);

    void setVelocity(sf::Vector2f v);
    sf::Vector2f getVelocity() const;
    sf::Vector2f getPosition() const;

    void setPosition(float x, float y);

    bool isAlive() const;
    void kill();
};
