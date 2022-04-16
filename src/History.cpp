#include <History.hpp>

void History::push(Memento memo, int queue) {
    switch (queue)
    {
        case History::UNDO_QUEUE:
            historyTrash.clear();
            history.push_back(memo);
            break;

        case History::REDO_QUEUE:
            historyTrash.push_back(memo);
            break;
    }
}

void History::clear() {
    historyTrash.clear();
    history.clear();
}

void History::undo() {
    if (this->history.size() == 0) {
        this->has_memo = false;
        return;
    }

    Memento snapshot = this->history.back();
    this->history.pop_back();

    this->snapshot = snapshot;
    this->has_memo = true;
}

void History::redo() {
    if (this->historyTrash.size() == 0) {
        this->has_memo = false;
        return;
    }

    Memento snapshot = this->historyTrash.back();
    this->historyTrash.pop_back();

    this->snapshot = snapshot;
    this->has_memo = true;
}

Memento History::get_snapshot() {
    this->has_memo = false;
    return this->snapshot;
}

bool History::has_snapshot() {
    return this->has_memo;
}