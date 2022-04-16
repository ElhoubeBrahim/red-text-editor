#ifndef Action_HRT
#define Action_HRT

#include <iostream>
#include <SFML/Graphics.hpp>
#include "EditorLine.hpp"

class Memento
{
    private:
        int row;
        int col;
        std::vector<EditorLine> lines;
        std::time_t timestamp;

    public:
        Memento() { }
        Memento(std::vector<EditorLine> lines, int row, int col);
        std::vector<int> get_coords();
        std::vector<EditorLine> get_lines();
        std::time_t get_time();
};

#endif
