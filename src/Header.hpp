#ifndef Header_HRT
#define Header_HRT

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Document.hpp"
#include "../env.hpp"

class Header
{
    private:
        int height = TOP_MARGIN;
        int button_width = 30;
        Document * document;
        
    public:
        Header(Document * document);
        void draw(sf::RenderWindow *window);
        void resize();
};

#endif
