#include "Document.hpp"

#include "Utils.hpp"
#include <math.h>
#include <fstream>
#include <map>

/**
 * @brief Construct a new Document:: Document object
 * 
 * @param path 
 */
Document::Document(std::string path) {
    this->open_file(path);
}

/**
 * @brief Check if the given path is valid
 * 
 */
void Document::validate_file_path() {
    // If the file does not exist
    if (this->file_path.empty() || !this->file_exists()) {
        // Break the program
        std::cout << Utils::colorify("Red Text Error: A valid input file is needed", "\033[31m") << '\n';
        std::cout << '\t' << "Can not open the file : " << this->file_path << ". No such file or directory." << '\n';
        exit(0);
    }
}

/**
 * @brief Open and load content of the chosed file
 * 
 * @param path 
 */
void Document::open_file(std::string path) {
    // Validate and setup file
    this->file_path = path;
    this->validate_file_path();
    std::cout << "Opening " << Utils::colorify(path, "\033[32m") << " ..." << '\n';

    // Load main font and lines
    this->load_fonts();
    this->load_lines();

    // Set up the cursor
    this->cursor.set_line(this->lines.at(0));
    this->get_cursor()->set_lines_count(this->lines.size());
}

/**
 * @brief Load document main fonts
 * 
 */
void Document::load_fonts() {
    this->font.loadFromFile(this->main_font);
    this->content_font.loadFromFile(this->document_font);
}

/**
 * @brief Set the document view
 * 
 * @param window 
 */
void Document::load_view(sf::RenderWindow * window) {
    this->view = EditorView(window);
    this->get_cursor()->set_view(&this->view);
}

/**
 * @brief If the document is saved
 * 
 * @return true 
 * @return false 
 */
bool Document::is_saved() {
    return this->saved;
}

/**
 * @brief Get the camera
 * 
 * @return sf::View 
 */
sf::View Document::get_view() {
    return this->view.get_camera();
}

/**
 * @brief Get colors according to the shosen theme
 * 
 * @param color 
 * @return sf::Color 
 */
sf::Color Document::get_theme_color(std::string color) {
    // Init colors container
    std::map<std::string, sf::Color> colors;

    // Check the theme
    switch (this->theme) {
        case LIGHT_THEME:
            // Light theme
            colors = ThemeColors::LightTheme().get_colors();
            break;

        case DARK_THEME:
            // Dark theme
            colors = ThemeColors::DarkTheme().get_colors();
            break;

        /*
         * More themes may be added here 
        */
        
        default:
            // Default is the dark
            colors = ThemeColors::DarkTheme().get_colors();
            break;
    }

    // Return the color if exists, else return black
    return colors.count(color) > 0 ? colors.at(color) : sf::Color(0, 0, 0);
}

/**
 * @brief Handle window resise
 * 
 * @param height 
 * @param width 
 */
void Document::resize_view(float height, float width) {
    this->view.resize(height, width);
}

/**
 * @brief Get the file name to print in the header as a title
 * 
 * @return std::string 
 */
std::string Document::get_file_name() {
    // Get the last position of "/"
    std::size_t position = this->file_path.find_last_of("/");
    // get file name
    std::string file_name = this->file_path.substr(position + 1, this->file_path.length());

    return file_name;
}

/**
 * @brief Get the main font
 * 
 * @return sf::Font 
 */
sf::Font * Document::get_main_font() {
    return &this->font;
}

/**
 * @brief Get the chosen theme
 * 
 * @return int 
 */
int Document::get_theme() {
    return this->theme;
}

/**
 * @brief Draw the document's content
 * 
 * @param window 
 */
void Document::draw(sf::RenderWindow *window) {
    // Init document dimentions
    this->max_height = 0;
    this->max_width = 0;

    // Init the counter
    int i = 0;

    // Loop through document lines
    for (EditorLine line : this->lines) {
        // Set the line colors according to the chosen theme
        line.set_colors(this->get_theme_color("text_color"), this->get_theme_color("content_color"));
        // Set the count number
        line.set_number(i);
        // Draw the number of the line in the margin
        window->draw(line.get_number_text());

        // Loop through line chars
        for (sf::Text character : line.get_content_chars()) {
            // Draw the char
            window->draw(character);
        }

        // Update the document dimentions
        this->max_height = this->max_height + LINE_HEIGHT;
        this->max_width = std::max(this->max_width, line.get_width());

        // Next line count
        i++;
    }

    // Draw the cursor
    if(Cursor::toggle_visibility()) window->draw(this->get_cursor()->get_shape());

    // Tell the camera about the document's dimentions
    this->view.set_max_height(this->max_height);
    this->view.set_max_width(this->max_width);

    // Highlight the active line
    this->heighlight_active_line(window);
}

/**
 * @brief Heighlight the active line
 * 
 * @param window 
 */
void Document::heighlight_active_line(sf::RenderWindow *window) {
    // Draw the heighlight rectangle
    sf::RectangleShape heighlight(sf::Vector2f(this->max_width + 100, LINE_HEIGHT + 4));
    heighlight.setFillColor(this->get_theme_color("heighlight"));
    heighlight.setPosition(LEFT_MARGIN - 3, TOP_MARGIN + (this->get_cursor()->row_number() * LINE_HEIGHT) - 1);
    window->draw(heighlight);
}

/**
 * @brief Get the cursor object
 * 
 * @return Cursor* 
 */
Cursor * Document::get_cursor() {
    return &this->cursor;
}

/**
 * @brief Check if the file exists
 * 
 * @return bool
 */
bool Document::file_exists() {
    std::ifstream file(this->file_path);
    return file.good();
}

/**
 * @brief Create lines objects
 * 
 */
void Document::load_lines() {
    // Init document lines
    this->lines.clear();
    // This is a helper variable
    std::string line;
    // Open the file
    std::ifstream file(this->file_path);

    // Loop through its lines
    while (getline(file, line)) {
        // Create new instance and push it to the lines vector
        this->lines.push_back(EditorLine(line, &this->font, &this->content_font));
    }

    // Close the file
    file.close();
}

/**
 * @brief Move cursor on click
 * 
 * @param x 
 * @param y 
 */
void Document::place_cursor_in(int x, int y) {
    // Guess the line and char numbers from coords
    std::vector<int> coords = this->get_document_coords(x, y);

    // Update the cursor's line to the current line
    this->get_cursor()->set_line(this->lines.at(coords.at(0)));
    // Move cursor
    this->get_cursor()->move_to(coords.at(0), coords.at(1));
}

/**
 * @brief Calculate the line and char numbers from coords
 * 
 * @param x 
 * @param y 
 * @return std::vector<int> 
 */
std::vector<int> Document::get_document_coords(int x, int y) {
    // Init the result vector
    std::vector<int> coords;

    // Get the line number and check if it's not outside of document boundaries
    int row = ((y / LINE_HEIGHT) >= this->lines.size()) 
        ? (this->lines.size() - 1) 
        : (y / LINE_HEIGHT);

    // Init col number
    int col = 0;
    float cursor_x = LEFT_MARGIN;

    // If the user clicks after the first char in each line
    if (x >= cursor_x + 5) {
        sf::FloatRect bounds;

        // Loop through line chars
        for (sf::Text char_text : this->lines.at(row).get_content_chars()) {
            // Calc the cursor x axis coord
            bounds = char_text.getLocalBounds();
            cursor_x = cursor_x + bounds.width + 3;
            // Count the chars numbers
            col++;

            // If we reach the clicked char
            if (cursor_x + 5 >= x || cursor_x >= x) break;
        }
    }

    // Return found line and char numbers
    coords.push_back(row);
    coords.push_back(col);
    return coords;
}

/**
 * @brief Handle user scroll event
 * 
 * @param event 
 */
void Document::handle_scroll(sf::Event event) {
    // Vertical scroll
    if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
        this->handle_vertical_scroll(event);
    // Horizontal scroll
    } else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) {
        this->handle_horizontal_scroll(event);
    }
}

/**
 * @brief Handle vertical scroll
 * 
 * @param event 
 */
void Document::handle_vertical_scroll(sf::Event event) {
    // If the user scrolls up
    if (event.mouseWheelScroll.delta > 0) {
        this->view.scroll_up();
    } else {
        this->view.scroll_down();
    }
}

/**

 * @brief Handle horizontal scroll
 * 
 * @param event 
 */
void Document::handle_horizontal_scroll(sf::Event event) {
    // If the user scrolls left
    if (event.mouseWheelScroll.delta > 0) {
        this->view.scroll_left();
    } else {
        this->view.scroll_right();
    }
}

/**
 * @brief Handle user typing
 * 
 * @param event 
 */
void Document::handle_user_input(sf::Event event) {
    // If shortcut mode is activated
    if (this->ctrl_is_pressed()) return;

    // Get the typed char
    sf::Uint32 c = event.text.unicode;
    // Get the current document coords
    int row = this->get_cursor()->row_number();
    int col = this->get_cursor()->col_number();

    // Check the value of the entered char
    switch (c)
    {
        // Break line '\n'
        case 13: {
            // Break the line content
            std::string content = this->lines.at(row).break_at(col);
            // Create a new line
            EditorLine new_line = EditorLine(content, &this->font, &this->content_font);
            // Insert the created line at the next position
            this->lines.insert(this->lines.begin() + row + 1, new_line);

            // Move the cursor to the next line
            this->get_cursor()->set_line(this->lines.at(row + 1));
            this->get_cursor()->move_to(row + 1, 0);
            this->get_cursor()->set_lines_count(this->lines.size());
            break;
        }

        // Delete char
        case 8: {
            // If the deleted char is a break line
            if (col == 0 && row != 0) {
                // Get the size of previous line
                col = this->lines.at(row - 1).get_size();

                // Merge the lines and erase one of them
                this->lines.at(row - 1).merge_with(this->lines.at(row));
                this->lines.erase(this->lines.begin() + row);

                // Move the cursor to the merge point
                this->get_cursor()->set_line(this->lines.at(row - 1));
                this->get_cursor()->move_to(row - 1, col);
                this->get_cursor()->set_lines_count(this->lines.size());
            } else if (col != 0) {
                // Delete the char
                this->lines.at(row).delete_char_at(col);
            
                // Move the cursor one step left
                this->get_cursor()->set_line(this->lines.at(row));
                this->get_cursor()->move_left();
            }
            break;
        }
    
        // Any other char
        default: {
            // Insert the char
            this->lines.at(row).insert_char_at((char)c, col);
            
            // Move cursor one step right
            this->get_cursor()->set_line(this->lines.at(row));
            this->get_cursor()->move_right();
            break;
        }
    }

    // Mark document as changed
    this->saved = false;
}

/**
 * @brief Move cursor when arrow is pressed
 * 
 * @param event 
 */
void Document::handle_arrows_press(sf::Event &event) {
    // If shortcut mode is activated
    if (this->ctrl_is_pressed()) return;

    // Get the document coords
    int row = this->get_cursor()->row_number();
    int col = this->get_cursor()->col_number();

    // Check the clicked key
    switch (event.key.code)
    {
        // Up arrow
        case sf::Keyboard::Up:
            // Move the cursor up
            if (row != 0) this->get_cursor()->set_line(this->lines.at(row - 1));
            this->get_cursor()->move_up();
            break;

        // Left arrow
        case sf::Keyboard::Left:
            // Move the cursor left
            if (col == 0 && row != 0) this->get_cursor()->set_line(this->lines.at(row - 1));
            this->get_cursor()->move_left();
            break;

        // Down arrow
        case sf::Keyboard::Down:
            // Move the cursor down
            if (row != this->lines.size() - 1) this->get_cursor()->set_line(this->lines.at(row + 1));
            this->get_cursor()->move_down();
            break;

        // Right arrow
        case sf::Keyboard::Right:
            // Move the cursor right
            this->get_cursor()->move_right();
            if (col == this->lines.at(row).get_size() && row != this->lines.size() - 1)
                this->get_cursor()->set_line(this->lines.at(row + 1));
            break;
        
        default:
            break;
    }

}

/**
 * @brief Handle keyboard shortcuts : ctrl + s, ctrl + z, ctrl + c ...
 * 
 * @param event 
 */
void Document::handle_shortcuts(sf::Event &event) {
    // Get the document coords
    int row = this->get_cursor()->row_number();
    int col = this->get_cursor()->col_number();

    // If "ctrl + s" is pressed
    if (this->ctrl_is_pressed() && event.key.code == sf::Keyboard::S) {
        // Save the file
        std::cout << "Saving File ..." << '\n';
        this->save();
        std::cout << "File saved " << Utils::colorify(this->file_path, "\033[32m") << '\n';
    }
}

/**
 * @brief Save the file
 * 
 */
void Document::save() {
    // Open the file
    std::ofstream file(this->file_path);

    // Loop through editor lines
    for (EditorLine line : this->lines) {
        // Write the line
        file << line.get_content() << '\n';
    }

    // Close the file
    file.close();

    // Mark document as saved
    this->saved = true;
}

/**
 * @brief Switch themes
 * 
 */
void Document::toggle_theme() {
    this->theme = !this->theme;
}

/**
 * @brief Check if shortcuts mode is activated
 * 
 * @return true | false 
 */
bool Document::ctrl_is_pressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
}