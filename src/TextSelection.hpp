#ifndef TextSelection_HRT
#define TextSelection_HRT

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../env.hpp"
#include "EditorLine.hpp"

class TextSelection
{
    private:
        std::vector<int> start;
        std::vector<int> end;
        std::string content;

    public:
        TextSelection();
        void clear();
        void clear_content();
        void copy();

        void set_start(int row, int col);
        void set_end(int row, int col);
        void add_content(std::string str);

        std::vector<std::vector<int>> get_boundaries();

        bool contains(int row, int col);
        bool empty();
        sf::RectangleShape get_drawing(sf::Text character, sf::Color bg);

    private:
        int direction();
};

#endif