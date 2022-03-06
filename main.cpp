#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "src/Document.hpp"

int main(int argc, char *argv[])
{

    /**
     * Parse the Path and Start the App
     * ===================================================
     */ 
    Document document((argc > 1) ? argv[1] : "");

    /**
     * Setup window object
     * ===================================================
     */
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Red Text Editor");
    window.setVerticalSyncEnabled(true);
    document.load_view(&window);

    sf::Color window_background(34, 34, 34);

    sf::Cursor user_cursor;
    if (user_cursor.loadFromSystem(sf::Cursor::Text))
        window.setMouseCursor(user_cursor);

    /**
     * Run the editor
     * ===================================================
     */
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // On window closed
            if (event.type == sf::Event::Closed) window.close();

            // Handle resize
            if (event.type == sf::Event::Resized) {
                document.resize_view(event.size.width, event.size.height);
            }

            // Handle scroll
            if (event.type == sf::Event::MouseWheelScrolled) {
                document.handle_scroll(event);
            }

            // On mouse click => Remove selections and Move cursor
            if (event.type == sf::Event::MouseButtonPressed) {

                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f coords = window.mapPixelToCoords(pixelPos);

                    int mouse_x = coords.x;
                    int mouse_y = coords.y;

                    document.place_cursor_in(mouse_x, mouse_y);
                }
            }

            // On user type => Change document content
            if (event.type == sf::Event::TextEntered) {
                document.handle_user_input(event);
            }

            // On user press => Handle special buttons: ctrl, shift, arrows, alt ...
            if (event.type == sf::Event::KeyPressed) {
                document.handle_arrows_press(event);
            }
        }

        // Set the background
        window.clear(window_background);
        // Set the view
        window.setView(document.get_view());
        // Draw the editor lines
        document.draw(&window);
        // Show the window
        window.display();
    }

    return 0;
}