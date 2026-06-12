#include "boss.h"
#include <cmath> // Do funkcji std::sin (animacja)
#include <cstdlib>

Boss::Boss(sf::Texture& texture, float x, float y, int health)
    : GameObject(x, y), hp(health), hitTimer(0.f), animationTime(0.f)
{
    sprite.setTexture(texture);

    // Ustawiamy środek kurczaka (origin), zeby animacja pulsowania byla od srodka
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    // Powiększamy Bossa
    sprite.setScale(1.5f, 1.5f);

    // Szybkość Bossa (porusza sie szybciej niz zwykla fala)
    velocity = sf::Vector2f(300.f, 0.f);

    syncVisual();
}

void Boss::syncVisual() {
    sprite.setPosition(position);
}

void Boss::update(float deltaTime) {
    GameObject::update(deltaTime);

    // --- ANIMACJA 1: Pulsowanie wielkosci (Punkt 7) ---
    animationTime += deltaTime;
    // Skala bazowa to 1.5, dodajemy sinusoide zeby lekko rosl i malal
    float scaleAnim = 1.5f + 0.15f * std::sin(animationTime * 5.0f);
    sprite.setScale(scaleAnim, scaleAnim);

    // --- ANIMACJA 2: Miganie na czerwono po trafieniu ---
    if (hitTimer > 0.f) {
        hitTimer -= deltaTime;
        sprite.setColor(sf::Color::Red);
    } else {
        sprite.setColor(sf::Color::White); // Powrot do normalnego koloru
    }

    // Odbijanie Bossa od krawedzi ekranu (zakladam 1280px z GameConfig)
    sf::FloatRect b = getBounds();
    if (b.left <= 0) {
        position.x = b.width / 2.0f; // Korekta pozycji przez origin
        velocity.x = std::abs(velocity.x); // Zmiana kierunku w prawo
    } else if (b.left + b.width >= 1280.f) {
        position.x = 1280.f - b.width / 2.0f;
        velocity.x = -std::abs(velocity.x); // Zmiana kierunku w lewo
    }
}

void Boss::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Boss::getBounds() const {
    return sprite.getGlobalBounds();
}

bool Boss::takeDamage() {
    hp--;
    hitTimer = 0.1f; // Miga na czerwono przez 0.1 sekundy
    if (hp <= 0) {
        kill();
        return true;
    }
    return false;
}

std::vector<std::unique_ptr<Egg>> Boss::dropSpreadEggs() const {
    std::vector<std::unique_ptr<Egg>> eggs;
    // Boss strzela częściej, np. ~2 razy na sekunde
    if (rand() % 30 == 0) {
        // Rzuca 3 jajka na raz z drobnym przesunieciem w poziomie
        eggs.push_back(std::make_unique<Egg>(position.x - 40.f, position.y + 50.f));
        eggs.push_back(std::make_unique<Egg>(position.x, position.y + 60.f));
        eggs.push_back(std::make_unique<Egg>(position.x + 40.f, position.y + 50.f));
    }
    return eggs;
}
