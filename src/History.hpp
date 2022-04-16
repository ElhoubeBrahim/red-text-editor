#ifndef History_HRT
#define History_HRT

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Memento.hpp"

class History 
{
    public:
        static const int REDO_QUEUE = 0;
        static const int UNDO_QUEUE = 1;

    private:
        std::vector<Memento> history;
        std::vector<Memento> historyTrash;

        Memento snapshot;
        bool has_memo = false;

    public:
        History() {};
        void push(Memento memo, int queue);
        void undo();
        void redo();
        void clear();

        Memento get_snapshot();
        bool has_snapshot();
};

#endif