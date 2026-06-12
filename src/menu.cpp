#include "menu.h"
#include <iostream>

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Blad wczytywania czcionki w menu!" << std::endl;
    }

    // Tytul Gry
    title.setFont(font);
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::Yellow);
    title.setString("CHICKEN INVADERS");
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2.0f, titleBounds.height / 2.0f);
    title.setPosition(width / 2.0f, height / 4.0f);

    // Opcje Menu
    std::vector<std::string> options = {"Graj", "Wczytaj z zapisu", "Wyjscie"};
    for (size_t i = 0; i < options.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(40);
        text.setString(options[i]);

        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        text.setPosition(width / 2.0f, height / 2.0f + i * 60.0f);

        // Domyslnie pierwsza opcja jest podswietlona (czerwona)
        if (i == 0) text.setFillColor(sf::Color::Red);
        else text.setFillColor(sf::Color::White);

        menuItems.push_back(text);
    }
    selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(title);
    for (const auto& item : menuItems) {
        window.draw(item);
    }
}

void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (static_cast<size_t>(selectedItemIndex + 1) < menuItems.size()) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

int Menu::getPressedItem() const {
    return selectedItemIndex;
}
