#include "Cursor.hpp"

int Cursor::blinks_freq = 30;
int Cursor::blinks_count = 0;
bool Cursor::visible = true;

/**
 * Default constructor
 */
Cursor::Cursor() : Cursor(0, 0) {};

/**
 * @brief Construct a new Cursor:: Cursor object
 * 
 * @param row
 * @param col 
 */
Cursor::Cursor(int row, int col) {
    // Set the line and char numbers
    this->rowN = row;
    this->colN = col;

    // Set dimentions
    sf::Vector2f size;
    size.x = this->width;
    size.y = this->height;

    // Set the background color
    sf::Color bgc(52, 152, 219);

    this->cursor.setSize(size);
    this->cursor.setFillColor(bgc);

    // Put the cursor at the beginning of the document
    this->cursor.setPosition(LEFT_MARGIN, 0);
}

/**
 * @brief Get the line number
 * 
 * @return int 
 */
int Cursor::row_number() {
    return this->rowN;
}

/**
 * @brief Get the char number
 * 
 * @return int 
 */
int Cursor::col_number() {
    return this->colN;
}

/**
 * @brief Set the window view
 * 
 * @param view 
 */
void Cursor::set_view(EditorView * view) {
    this->view = view;
}

/**
 * @brief Set the editor line object
 * 
 * @param line 
 */
void Cursor::set_line(EditorLine line) {
    this->line = line;
}

/**
 * @brief Move the cursor to a position
 * 
 * @param row 
 * @param col 
 */
void Cursor::move_to(int row, int col) {
    // Set the line and char numbers
    this->rowN = row;
    this->colN = col;

    // Init coords
    float x = LEFT_MARGIN;
    float y = row * LINE_HEIGHT;

    // If it's not at the beginning of the line
    if (col != 0) {
        sf::FloatRect bounds;
        col = 0;
        
        // Loop through chars of the current line
        for (sf::Text char_text : this->line.get_content_chars()) {
            // Calculate the x value after the current char
            bounds = char_text.getLocalBounds();
            x = x + bounds.width + 3;
            // Move one column forward
            col++;

            // If we reach the target char
            if (col == this->colN) break;
        }
    }

    // Set the char number + position
    this->colN = col;
    this->cursor.setPosition(x, y);

    // Scroll if the cursor is outside of the camera - view
    sf::View camera = this->view->get_camera();
    double height = camera.getSize().y;
    double width = camera.getSize().x;
    double cam_x = camera.getCenter().x;
    double cam_y = camera.getCenter().y;

    // If the cursor is in the left of the camera
    if (x <= cam_x - (width / 2) + CHAR_WIDTH) {
        this->view->set_center(
            cam_x - (cam_x - (width / 2) - x) - (CHAR_WIDTH * 5),
            this->view->get_camera().getCenter().y
        );
    }

    // If the cursor is in the right of the camera
    if (x >= cam_x + (width / 2) - CHAR_WIDTH) {
        this->view->set_center(
            cam_x + (x - (cam_x + (width / 2))) + (CHAR_WIDTH * 5),
            this->view->get_camera().getCenter().y
        );
    }

    // If the cursor is in the top of the camera
    if (y <= cam_y - (height / 2) + LINE_HEIGHT) {
        this->view->set_center(
            this->view->get_camera().getCenter().x,
            cam_y - (cam_y - (height / 2) - y) - (row != 0 ? LINE_HEIGHT : 0)
        );
    }

    // If the cursor is in the bottom of the camera
    if (y >= cam_y + (height / 2) - LINE_HEIGHT) {
        this->view->set_center(
            this->view->get_camera().getCenter().x,
            cam_y + (y - (cam_y + (height / 2))) + (LINE_HEIGHT * 2)
        );
    }
}

/**
 * @brief Move the cursor up one line
 */
void Cursor::move_up() {
    // If it's not the first line
    if (this->rowN != 0) 
        this->move_to(this->rowN - 1, this->colN);
};

/**
 * @brief Move the cursor left one char
 */
void Cursor::move_left() {
    // If it's not the first char
    if (this->colN != 0) 
        this->move_to(this->rowN, this->colN - 1);
    else if (this->rowN != 0) {
        // if it's the first char
        this->colN = this->line.get_size();
        // Move up if it's not the first line
        this->move_up();
    }
};

/**
 * @brief Move the cursor down one line
 */
void Cursor::move_down() {
    // If it's not the last line
    if (this->rowN < this->lines_count - 1)
        this->move_to(this->rowN + 1, this->colN);
};

/**
 * @brief Move the cursor right one char
 */
void Cursor::move_right() {
    // If it's not the last char in the line
    if (this->colN < this->line.get_size())
        this->move_to(this->rowN, this->colN + 1);
    else if (this->rowN < this->lines_count - 1) {
        // if it's the last char
        this->colN = 0;
        // Move down if it's not the last line
        this->move_down();
    }
};

/**
 * @brief Set the number of document lines
 * 
 * @param count 
 */
void Cursor::set_lines_count(int count) {
    this->lines_count = count;
}

/**
 * @brief Get the cursor rectangle to draw
 * 
 * @return sf::RectangleShape 
 */
sf::RectangleShape Cursor::get_shape() {
    return this->cursor;
}

/**
 * @brief Blink the cursor - show and hide
 * 
 * @return bool
 */
bool Cursor::toggle_visibility() {
    if (++blinks_count >= blinks_freq) {
        visible = !visible;
        blinks_count = 0;
    }

    return visible;
}
