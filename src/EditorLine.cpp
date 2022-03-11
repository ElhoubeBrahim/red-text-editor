#include "EditorLine.hpp"

#include "../env.hpp"
#include <math.h>

/**
 * @brief Default constructor
 * 
 */
EditorLine::EditorLine() {};

/**
 * @brief Construct a new Editor Line:: Editor Line object
 * 
 * @param text 
 * @param _main_font 
 * @param _content_font 
 */
EditorLine::EditorLine(std::string text, sf::Font *_main_font, sf::Font *_content_font) {
    // Init attributs
    this->content = text;
    this->main_font = _main_font;
    this->content_font = _content_font;
    instances_count++;
    this->line_number = instances_count - 1;
    active = (this->line_number == 1);

    // Draw the line
    this->draw_number();
    this->draw_chars();
}

/**
 * @brief Get the line number widget
 * 
 * @return sf::Text 
 */
sf::Text EditorLine::get_number_text() {
    return this->number_text;
}

/**
 * @brief Get the list of line chars widgets
 * 
 * @return std::vector<sf::Text> 
 */
std::vector<sf::Text> EditorLine::get_content_chars() {
    return this->line_chars;
}

/**
 * @brief Get the numbet of chars
 * 
 * @return int 
 */
int EditorLine::get_size() {
    return this->line_chars.size();
}

/**
 * @brief Get the line widget width
 * 
 * @return float 
 */
float EditorLine::get_width() {
    return this->width;
}

/**
 * @brief Get the line text content
 * 
 * @return std::string 
 */
std::string EditorLine::get_content() {
    return this->content;
}

/**
 * @brief Draw text widget
 * 
 * @param content 
 * @param x 
 * @param is_content 
 * @return sf::Text 
 */
sf::Text EditorLine::draw_text(std::string content, int x, bool is_content) {
    // Init new sfml text widget
    sf::Text text;

    // Set text global properties - font, size and content
    text.setFont((is_content) ? *this->content_font : *this->main_font);
    text.setCharacterSize(24);
    text.setString(content);

    // Set the text position
    // 65 - bounds.width => rtl text such as line number
    sf::FloatRect bounds = text.getLocalBounds();
    text.setPosition((is_content) ? x : 65 - bounds.width, TOP_MARGIN + (LINE_HEIGHT * this->line_number));
    
    // Calculate the line width
    if (is_content) this->width += bounds.width + 3;

    // Return widget
    return text;
}

/**
 * @brief Draw line number widget
 * 
 */
void EditorLine::draw_number() {
    // Draw text widget
    this->number_text = this->draw_text(std::to_string(this->line_number), 10, false);
    // Set color
    this->number_text.setFillColor(sf::Color(119, 119, 119));
}

/**
 * @brief Draw line chars widgets
 * 
 */
void EditorLine::draw_chars() {
    // Init line width
    this->width = 0;
    
    // Init vars
    sf::Text char_text;
    int x = LEFT_MARGIN;
    sf::FloatRect bounds;

    // Foreach char in the line content
    for (char c : this->content) {
        // Draw char widget
        char_text = this->draw_text(std::string(1, c), x, true);
        char_text.setFillColor(sf::Color(221, 221, 221));

        // Calculate line width
        bounds = char_text.getLocalBounds();
        x = x + bounds.width + 3;

        // Add the char widget to the 
        this->line_chars.push_back(char_text);
    }
}

/**
 * @brief Insert char at the given position
 * 
 * @param c 
 * @param col 
 */
void EditorLine::insert_char_at(char c, int col) {
    // Add the entered char to the text content
    this->content.insert(col, 1, c);
    // Remove old created chars
    this->line_chars.clear();
    // Redraw chars
    this->draw_chars();
}

/**
 * @brief Delete char at the given position
 * 
 * @param col 
 */
void EditorLine::delete_char_at(int col) {
    // Remove a char from the text content
    this->content.erase(col - 1, 1);
    // Remove old created chars
    this->line_chars.clear();
    // Redraw chars
    this->draw_chars();
}

/**
 * @brief Break line at the given position
 * 
 * @param col 
 * @return std::string 
 */
std::string EditorLine::break_at(int col) {
    // Get the part text to remove
    std::string removed_text = this->content.substr(col);
    
    // Remove text after break position
    this->content.resize(col);
    // Remove old created chars
    this->line_chars.clear();
    // Redraw chars
    this->draw_chars();

    // Return removed text to use it in the new line
    return removed_text;
}

/**
 * @brief Merge two lines
 * 
 * @param line 
 */
void EditorLine::merge_with(EditorLine line) {
    // Get the hosted line content
    std::string content = line.get_content();

    // Merge them
    this->content += content;
    // Remove old created chars
    this->line_chars.clear();
    // Redraw chars
    this->draw_chars();
}

/**
 * @brief Set the line number
 * 
 * @param n 
 */
void EditorLine::set_number(int n) {
    this->line_number = n;

    // Redraw the line
    this->line_chars.clear();
    this->draw_number();
    this->draw_chars();
}

int EditorLine::instances_count = 0;
