#ifndef EditorView_HRT
#define EditorView_HRT

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../env.hpp"

class EditorView
{
    private:
        int delta_scroll = LINE_HEIGHT;
        sf::View camera;

        float content_height;
        float content_width;
        
    public:
        EditorView();
        EditorView(sf::RenderWindow * window);
        sf::View get_camera();

        void set_center(float x, float y);
        void resize(float height, float width);

        void set_max_height(float height);
        void set_max_width(float width);

        void scroll_up();
        void scroll_down();
        void scroll_left();
        void scroll_right();

        void zoom_in();
        void zoom_out();
        
};


#endif