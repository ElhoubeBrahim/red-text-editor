#include "TextSelection.hpp"

/**
 * @brief Construct a new Text Selection:: Text Selection object
 * 
 */
TextSelection::TextSelection() {
    // Init boundaries
    this->clear();
}

/**
 * @brief Init selection boundaries
 * 
 */
void TextSelection::clear() {
    // Init start coords
    this->set_start(-1, -1);
    // Init end coords
    this->set_end(-1, -1);
    // Delete selected text
    this->clear_content();
}

/**
 * @brief Clear selected text content
 * 
 */
void TextSelection::clear_content() {
    this->content.clear();
}

/**
 * @brief Copy selected text to clipboard
 * 
 */
void TextSelection::copy() {
    sf::Clipboard::setString(this->content);
}

/**
 * @brief Set selection zone start coords
 * 
 * @param row 
 * @param col 
 */
void TextSelection::set_start(int row, int col) {
    this->start.clear();
    this->start.push_back(row);
    this->start.push_back(col);
}

/**
 * @brief Set selection zone end coords
 * 
 * @param row 
 * @param col 
 */
void TextSelection::set_end(int row, int col) {
    this->end.clear();
    this->end.push_back(row);
    this->end.push_back(col);
}

/**
 * @brief Add text to already selected text content
 * 
 * @param str 
 */
void TextSelection::add_content(std::string str) {
    this->content.append(str);
}

/**
 * @brief Get selection start and end coords
 * 
 * @return std::vector<std::vector<int>> 
 */
std::vector<std::vector<int>> TextSelection::get_boundaries() {
    std::vector<std::vector<int>> boundaries;

    if (
        // If it is a normal select - From start to end
        this->start.at(0) < this->end.at(0) ||
        (
            this->start.at(0) == this->end.at(0) && 
            this->start.at(1) < this->end.at(1)
        )
    ) {
        boundaries.push_back(this->start);
        boundaries.push_back(this->end);
    } else { // From end to start
        boundaries.push_back(this->end);
        boundaries.push_back(this->start);
    }

    return boundaries;
}

/**
 * @brief Check if the selection zone is empty
 * 
 * @return true 
 * @return false 
 */
bool TextSelection::empty() {
    return (
        start.at(0) == end.at(0) &&
        start.at(1) == end.at(1)
    );
}

/**
 * @brief Check if a given char coords is in the selection zone
 * 
 * @param row 
 * @param col 
 * @return true 
 * @return false 
 */
bool TextSelection::contains(int row, int col) {
    // Get the selection direction
    int dir = this->direction();

    // If only one line is selected
    if (start.at(0) == end.at(0)) {
        return (
            start.at(0) == row &&
            start.at(1) * dir <= col * dir &&
            end.at(1) * dir >= col * dir
        );
    }

    // Else
    return (
        // If it's in the first row in selection
        (start.at(0) == row && start.at(1) * dir <= col * dir) ||
        // If it's in the last row in selection
        (end.at(0) == row && end.at(1) * dir >= col * dir) ||
        // If it's in the middle of the selection
        (start.at(0) * dir < row * dir && end.at(0) * dir > row * dir)
    );
}

/**
 * @brief Get the selection rectangle highlighter
 * 
 * @param character 
 * @param bg 
 * @return sf::RectangleShape 
 */
sf::RectangleShape TextSelection::get_drawing(sf::Text character, sf::Color bg) {
    // Get slected char dimentions
    sf::FloatRect bounds = character.getLocalBounds();

    // Create highlighter rectange
    sf::RectangleShape selection(sf::Vector2f(bounds.width + 3, LINE_HEIGHT));
    selection.setFillColor(bg);
    selection.setPosition(character.getPosition().x, character.getPosition().y);
    
    return selection;
}

/**
 * @brief Get the selection's direction
 * 
 * @return int 
 */
int TextSelection::direction() {
    // If there is no selection
    if (this->empty()) return 0;

    // If we select back to top
    if (
        start.at(0) > end.at(0) || 
        (
            start.at(0) == end.at(0) && 
            start.at(1) > end.at(1)
        )
    ) return -1;
    
    // Else
    return 1;
}
