// GameObject.h
#pragma once
#include <SFML/Graphics.hpp>

// Klasa bazowa dla wszystkich obiektow gry (statek, kurczaki, pociski, bonusy).
// Definiuje wspolny interfejs (polimorfizm) oraz wspolne dane ruchu.
class GameObject {
protected:
    sf::Vector2f position;     // pozycja w pikselach
    sf::Vector2f velocity;     // predkosc liniowa w pikselach/sekunde
    float rotation;            // aktualny obrot w stopniach
    float rotationSpeed;       // predkosc obrotu w stopniach/sekunde
    bool alive;                 // czy obiekt powinien zostac usuniety z kontenera

    // Synchronizuje wewnetrzny sprite/shape klasy pochodnej z position/rotation.
    // Domyslnie nic nie robi - klasy pochodne nadpisuja wg potrzeb.
    virtual void syncVisual() {}

public:
    GameObject(float x = 0.f, float y = 0.f);
    virtual ~GameObject() = default;

    // Aktualizuje pozycje na podstawie predkosci i obrot na podstawie rotationSpeed.
    // Klasy pochodne moga to nadpisac, ale powinny wywolac GameObject::update(dt).
    virtual void update(float deltaTime);

    // Czysto wirtualne - kazda klasa pochodna musi miec wlasna logike rysowania
    virtual void draw(sf::RenderWindow& window) const = 0;

    // Czysto wirtualne - granice do kolizji
    virtual sf::FloatRect getBounds() const = 0;

    // Bezposrednie przesuniecie pozycji (np. formacja kurczakow schodzaca nizej)
    void move(sf::Vector2f offset);

    void setVelocity(sf::Vector2f v);
    sf::Vector2f getVelocity() const;
    sf::Vector2f getPosition() const;

    void setPosition(float x, float y);

    bool isAlive() const;
    void kill();
};
