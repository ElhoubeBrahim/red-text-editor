#include "EditorView.hpp"

#include "../env.hpp"

/**
 * @brief Default constructor
 * 
 */
EditorView::EditorView() {}

/**
 * @brief Construct a new Editor View:: Editor View object
 * 
 * @param window 
 */
EditorView::EditorView(sf::RenderWindow * window) {
    // Create a new window view
    this->camera = sf::View(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
}

/**
 * @brief Get the window view
 * 
 * @return sf::View 
 */
sf::View EditorView::get_camera() {
    return this->camera;
}

/**
 * @brief Set the camera position
 * 
 * @param x 
 * @param y 
 */
void EditorView::set_center(float x, float y) {
    this->camera.setCenter(x, y);
}

/**
 * @brief Resize the window
 * 
 * @param height 
 * @param width 
 */
void EditorView::resize(float height, float width) {
    this->camera = sf::View(sf::FloatRect(0, 0, height, width));
}

/**
 * @brief Set document max height
 * 
 * @param height 
 */
void EditorView::set_max_height(float height) {
    this->content_height = height;
}


/**
 * @brief Set document max width
 * 
 * @param height 
 */
void EditorView::set_max_width(float width) {
    this->content_width = width;
}

/**
 * @brief Scroll document up
 * 
 */
void EditorView::scroll_up() {
    // Get camera height and y coord
    double height = this->camera.getSize().y;
    double cam_y = this->camera.getCenter().y;

    // If the camera didn't reach the top
    if (cam_y - (height / 2) > 0)
        // Move it up
        this->camera.move(0, -this->delta_scroll);
}

/**
 * @brief Scroll document down 
 * 
 */
void EditorView::scroll_down() {
    // Get camera height and y coord
    double height = this->camera.getSize().y;
    double cam_y = this->camera.getCenter().y;

    // If the camera didn't reach the end
    if (cam_y + (height / 2) < this->content_height + 500)
        // Move it down
        this->camera.move(0, this->delta_scroll);
}

/**
 * @brief Scroll document left
 * 
 */
void EditorView::scroll_left() {
    // Get camera width and x coord
    double width = this->camera.getSize().x;
    double cam_x = this->camera.getCenter().x;

    // If the camera didn't reach the line start
    if (cam_x - (width / 2) > 0)
        // Move it left
        this->camera.move(-this->delta_scroll, 0);
}

/**
 * @brief Scroll document right
 * 
 */
void EditorView::scroll_right() {
    // Get camera width and x coord
    double width = this->camera.getSize().x;
    double cam_x = this->camera.getCenter().x;

    // If the camera didn't reach the line end
    if (cam_x + (width / 2) < LEFT_MARGIN + this->content_width + 100)
        // Move it right
        this->camera.move(this->delta_scroll, 0);
}