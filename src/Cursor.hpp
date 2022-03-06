#ifndef Cursor_HRT
#define Cursor_HRT

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../env.hpp"
#include "EditorLine.hpp"
#include "EditorView.hpp"

class Cursor
{
    private:
        int rowN;
        int colN;
        EditorLine line;
        int lines_count = 0;

        EditorView * view;

        static int blinks_freq;
        static int blinks_count;
        static bool visible;

        const int height = LINE_HEIGHT;
        const int width = 3;

    public:
        sf::RectangleShape cursor;

    public:
        Cursor();
        Cursor(int row, int col);

        int row_number();
        int col_number();

        void set_view(EditorView * view);

        void move_to(int row, int col);

        void move_up();
        void move_left();
        void move_down();
        void move_right();

        sf::RectangleShape get_shape();
        static bool toggle_visibility();
        void set_lines_count(int count);
        void set_line(EditorLine line);
};

#endif