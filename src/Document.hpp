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
        
        int theme = DARK_THEME;

        std::string file_path;
        sf::Font font;
        sf::Font content_font;
        EditorView view;
        std::vector<EditorLine> lines;
        Cursor cursor = Cursor(0, 0);

        float max_height;
        float max_width;

        bool saved = true;

    public:
        Document(std::string path);
        void validate_file_path();
        void open_file(std::string path);
        void load_lines();
        void load_fonts();
        bool is_saved();

        std::string get_file_name();
        sf::Font * get_main_font();

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

        sf::Color get_theme_color(std::string color);
        int get_theme();

        void save();
        void toggle_theme();

    private:
        std::vector<int> get_document_coords(int x, int y);
        bool file_exists();

        bool ctrl_is_pressed();

        void handle_vertical_scroll(sf::Event event);
        void handle_horizontal_scroll(sf::Event event);

        void heighlight_active_line(sf::RenderWindow *window);
};

#endif