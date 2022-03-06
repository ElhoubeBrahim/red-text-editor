#ifndef EditorLine_HRT
#define EditorLine_HRT

#include <iostream>
#include <SFML/Graphics.hpp>

class EditorLine
{
    private:
        std::string content;
        static int instances_count;
        int line_number = 0;
        bool active;
        sf::Font *main_font;
        sf::Font *content_font;
        int size;
        float width = 0;

        sf::Text number_text;

        std::vector<sf::Text> line_chars;
    
    public:
        EditorLine();
        EditorLine(std::string text, sf::Font *_main_font, sf::Font *_content_font);
        sf::Text get_number_text();
        std::vector<sf::Text> get_content_chars();
        int get_size();
        std::string get_content();
        float get_width();

        void insert_char_at(char c, int col);
        void delete_char_at(int col);
        std::string break_at(int col);
        void merge_with(EditorLine line);

        void set_number(int n);

    private:
        sf::Text draw_text(std::string content, int x, bool is_content);
        void draw_number();
        void draw_chars();
};

#endif