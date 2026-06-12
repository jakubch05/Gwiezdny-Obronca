#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuItems;
    int selectedItemIndex;

public:
    Menu(float width, float height);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getPressedItem() const;
};
