#include "Memento.hpp"

/**
 * @brief Construct a new Memento:: Memento object
 * 
 * @param lines
 * @param row 
 * @param col 
 */
Memento::Memento(std::vector<EditorLine> lines, int row, int col) {
    this->row = row;
    this->col = col;
    this->lines = lines;
    this->timestamp = std::time(0);
}
/**
 * @brief Row, Col numbers getter
 * 
 * @return std::vector<int> 
 */
std::vector<int> Memento::get_coords() {
    std::vector<int> coords;
    coords.push_back(this->row);
    coords.push_back(this->col);

    return coords;
}

/**
 * @brief Lines getter
 * 
 * @return std::vector<EditorLine> 
 */
std::vector<EditorLine> Memento::get_lines() {
    return this->lines;
}

/**
 * @brief Timestamp getter
 * 
 * @return std::time_t 
 */
std::time_t Memento::get_time() {
    return this->timestamp;
}