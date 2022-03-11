#include "Header.hpp"

Header::Header(Document * document) {
    this->document = document;
}

void Header::draw(sf::RenderWindow *window) {
    // Get window width
    float width = window->getSize().x;

    // Header container
    sf::RectangleShape container(sf::Vector2f(width, this->height));
    container.setFillColor(sf::Color(17, 17, 17));

    // Adding title to the header
    sf::Text title;
    title.setString(this->document->get_file_name());
    title.setFont(*this->document->get_main_font());
    title.setFillColor(sf::Color(255, 255, 255));
    title.setCharacterSize(24);
    title.setPosition((this->height / 2) - 10, 20);

    // Generate the theme switcher button
    sf::Texture bg1;
    bg1.loadFromFile("assets/images/icons/mode.png", sf::IntRect(0, 0, this->button_width, this->button_width));
    bg1.setSmooth(true);
    sf::Sprite theme_button;
    theme_button.setTexture(bg1, true);
    theme_button.setPosition(width - 60, (this->height / 2) - (this->button_width / 2));

    // Generate the save button
    sf::Texture bg2;
    bg2.loadFromFile("assets/images/icons/save.png", sf::IntRect(0, 0, this->button_width, this->button_width));
    bg2.setSmooth(true);
    sf::Sprite save_button;
    save_button.setTexture(bg2, true);
    save_button.setPosition(width - (60 + this->button_width + 10), (this->height / 2) - (this->button_width / 2));

    // Generate the theme switcher button
    sf::Texture bg3;
    bg3.loadFromFile("assets/images/icons/file.png", sf::IntRect(0, 0, this->button_width, this->button_width));
    bg3.setSmooth(true);
    sf::Sprite file_button;
    file_button.setTexture(bg3, true);
    file_button.setPosition(width - (60 + 2 * this->button_width + 20), (this->height / 2) - (this->button_width / 2));

    // Draw the header
    window->draw(container);

    // Draw the title
    window->draw(title);

    // Draw buttons
    window->draw(theme_button);
    window->draw(save_button);
    window->draw(file_button);
}

void Header::resize() { }