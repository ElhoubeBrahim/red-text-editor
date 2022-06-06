#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "src/Document.hpp"
#include "src/Header.hpp"

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

    sf::Cursor user_cursor;

    // Set the app logo
    sf::Image icon;
    icon.loadFromFile("assets/images/logo.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    /**
     * Create the editor header
     * ===================================================
     */
    Header header(&document, &window);

    /**
     * Run the editor
     * ===================================================
     */
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // On window closed
            if (event.type == sf::Event::Closed) window.close();

            // On mouse move
            if (event.type == sf::Event::MouseMoved) {
                // Get cursor coords
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f coords = window.mapPixelToCoords(pixelPos);

                int mouse_x = coords.x;
                int mouse_y = coords.y;

                // If the cursor is inside the documenr
                if (mouse_x > LEFT_MARGIN && mouse_y > TOP_MARGIN) {
                    // Change to type cursor
                    if (user_cursor.loadFromSystem(sf::Cursor::Text))
                        window.setMouseCursor(user_cursor);
                } else {
                    // Change to normal cursor
                    if (user_cursor.loadFromSystem(sf::Cursor::Arrow))
                        window.setMouseCursor(user_cursor);
                }
            }

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
                // Unselect text
                document.get_text_selection()->clear();

                // If the left mouse button is clicked
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Get cursor coords
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f coords = window.mapPixelToCoords(pixelPos);

                    int mouse_x = coords.x;
                    int mouse_y = coords.y - TOP_MARGIN;

                    // Move document cursor
                    if (mouse_y >= 0) {
                        document.mouse_clicked = true;
                        document.place_cursor_in(mouse_x, mouse_y);
                    }

                    // Check if a button is clicked in the header
                    header.handle_click(event);
                }
            }

            // If the mouse click id done
            if (event.type == sf::Event::MouseButtonReleased) {
                document.mouse_clicked = false;
            }

            // If mouse cursor moved on screen
            if (event.type == sf::Event::MouseMoved) {
                // If drag => click + move
                if (document.mouse_clicked) {
                    // Get cursor coords
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f coords = window.mapPixelToCoords(pixelPos);

                    int mouse_x = coords.x;
                    int mouse_y = coords.y - TOP_MARGIN;

                    if (mouse_y >= 0)
                        // Create a new text selection
                        document.select_text(mouse_x, mouse_y);
                }
            }

            // On user type => Change document content
            if (event.type == sf::Event::TextEntered) {
                document.handle_user_input(event);
            }

            // On user press => Handle special buttons: ctrl, shift, arrows, alt ...
            if (event.type == sf::Event::KeyPressed) {
                document.handle_arrows_press(event);
                document.handle_shortcuts(event);
            }
        }

        // Set the background
        window.clear(document.get_theme_color("bg"));
        // Set the view
        window.setView(document.get_view());
        // Draw the editor lines
        document.draw(&window);
        // Draw the editor header
        window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y - TOP_MARGIN)));
        header.set_window(&window);
        header.draw();
        // Reset the view
        window.setView(document.get_view());
        // Show the window
        window.display();
    }

    return 0;
}