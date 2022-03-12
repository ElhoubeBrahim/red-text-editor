#include "Header.hpp"

Header::Header(Document * document, sf::RenderWindow * window) {
    this->document = document;
    this->window = window;
}

void Header::draw() {
    // Header container
    sf::RectangleShape container(sf::Vector2f(this->window->getSize().x, this->height));
    container.setFillColor(sf::Color(17, 17, 17));

    // Adding title to the header
    sf::Text title;
    title.setString(this->document->get_file_name());
    title.setFont(*this->document->get_main_font());
    title.setFillColor(sf::Color(255, 255, 255));
    title.setCharacterSize(24);
    title.setPosition((this->height / 2) - 10, 20);

    // Draw the header
    this->window->draw(container);

    // Draw the title
    this->window->draw(title);

    // Draw buttons
    this->draw_theme_button();
    this->draw_save_button();
    this->draw_file_button();
}

void Header::resize() { }

void Header::set_window(sf::RenderWindow * window) {
    this->window = window;
}

void Header::handle_click(sf::Event event) {
    // Get mouse coords
    int x = event.mouseButton.x;
    int y = event.mouseButton.y;

    // If the header buttons are clicked
    if (
        y >= (this->height / 2) - (this->button_width / 2) && 
        y <= (this->height / 2) - (this->button_width / 2) + this->button_width
    ) {
        // Get window width
        float width = this->window->getSize().x;
        
        // If theme button is clicked
        if (x >= width - 60 && x <= width - 60 + this->button_width) {
            std::cout << "Toggling theme" << '\n';
        }

        // If save button is clicked
        if (x >= width - (60 + this->button_width + 10) && x <= width - (60 + this->button_width + 10) + this->button_width) {
            this->document->save();
        }

        // If file button is clicked
        if (x >= width - (60 + 2 * this->button_width + 20) && x <= width - (60 + 2 * this->button_width + 20) + this->button_width) {
            std::cout << "Opening file" << '\n';
        }
    }
}

void Header::draw_theme_button() {
    // Setup the icon
    sf::Texture bg;
    bg.loadFromFile("assets/images/icons/mode.png", sf::IntRect(0, 0, this->button_width, this->button_width));
    bg.setSmooth(true);

    // Draw the button
    sf::Sprite button;
    button.setTexture(bg, true);
    button.setPosition(window->getSize().x - 60, (this->height / 2) - (this->button_width / 2));

    this->window->draw(button);
}

void Header::draw_save_button() {
    // Setup the icon
    sf::Texture bg;
    bg.loadFromFile("assets/images/icons/save.png", sf::IntRect(0, 0, this->button_width, this->button_width));
    bg.setSmooth(true);

    // Draw the button
    sf::Sprite button;
    button.setTexture(bg, true);
    button.setPosition(window->getSize().x - (60 + this->button_width + 10), (this->height / 2) - (this->button_width / 2));

    this->window->draw(button);
}

void Header::draw_file_button() {
    // Setup the icon
    sf::Texture bg;
    bg.loadFromFile("assets/images/icons/file.png", sf::IntRect(0, 0, this->button_width, this->button_width));
    bg.setSmooth(true);

    // Draw the button
    sf::Sprite button;
    button.setTexture(bg, true);
    button.setPosition(window->getSize().x - (60 + 2 * this->button_width + 20), (this->height / 2) - (this->button_width / 2));

    this->window->draw(button);
}