#ifndef Document_HRT
#define Document_HRT

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../env.hpp"
#include "EditorLine.hpp"
#include "EditorView.hpp"
#include "Cursor.hpp"

class Document
{
    private:
        const std::string app_name = APP_NAME;
        const std::string main_font = MAIN_FONT;
        const std::string document_font = CONTENT_FONT;

        std::string file_path;
        sf::Font font;
        sf::Font content_font;
        EditorView view;
        std::vector<EditorLine> lines;
        Cursor cursor = Cursor(0, 0);

        float max_height;
        float max_width;

    public:
        Document(std::string path);
        void validate_file_path();
        void load_lines();
        void load_fonts();

        void load_view(sf::RenderWindow * window);
        sf::View get_view();
        void resize_view(float height, float width);

        void draw(sf::RenderWindow *window);
        Cursor * get_cursor();
        void place_cursor_in(int x, int y);

        void handle_scroll(sf::Event event);
        void handle_user_input(sf::Event event);
        void handle_arrows_press(sf::Event &event);
        void handle_shortcuts(sf::Event &event);

    private:
        std::vector<int> get_document_coords(int x, int y);
        bool file_exists();
        void save();

        bool ctrl_is_pressed();

        void handle_vertical_scroll(sf::Event event);
        void handle_horizontal_scroll(sf::Event event);
};

#endif