#ifndef Header_HRT
#define Header_HRT

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Document.hpp"
#include "../env.hpp"

class Header
{
    private:
        int height = TOP_MARGIN - 10;
        int button_width = 30;
        Document * document;
        sf::RenderWindow * window;
        
    public:
        Header(Document * document, sf::RenderWindow * window);
        void draw();
        void resize();
        void handle_click(sf::Event event);
        void set_window(sf::RenderWindow * window);

    private:
        void draw_theme_button();
        void draw_save_button();
        void draw_file_button();
};

#endif
