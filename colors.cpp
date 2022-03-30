#ifndef ThemeColors_HRT
#define ThemeColors_HRT

#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>

namespace ThemeColors
{
    class Theme {
        protected:
            sf::Color BG;
            sf::Color WHITE;
            sf::Color HEADER_BG;
            sf::Color TEXT_COLOR;
            sf::Color CONTENT_COLOR;
            sf::Color HEIGHLIGHT;

        public:
            std::map<std::string, sf::Color> get_colors() {
                std::map<std::string, sf::Color> colors;

                colors.insert(std::pair<std::string, sf::Color>("bg", this->BG));
                colors.insert(std::pair<std::string, sf::Color>("white", this->WHITE));
                colors.insert(std::pair<std::string, sf::Color>("header_bg", this->HEADER_BG));
                colors.insert(std::pair<std::string, sf::Color>("text_color", this->TEXT_COLOR));
                colors.insert(std::pair<std::string, sf::Color>("content_color", this->CONTENT_COLOR));
                colors.insert(std::pair<std::string, sf::Color>("heighlight", this->HEIGHLIGHT));

                return colors;
            }
    };

    class DarkTheme : public Theme
    {
        public:
            DarkTheme() {
                this->BG = sf::Color(41,45,52);
                this->WHITE = sf::Color(255, 255, 255);
                this->HEADER_BG = sf::Color(33, 37, 43);
                this->TEXT_COLOR = sf::Color(119, 119, 119);
                this->CONTENT_COLOR = sf::Color(221, 221, 221);
                this->HEIGHLIGHT = sf::Color(255, 255, 255, 50);
            }
    };

    class LightTheme : public Theme
    {
        public:
            LightTheme() {
                this->BG = sf::Color(250, 250, 250);
                this->WHITE = sf::Color(0, 0, 0);
                this->HEADER_BG = sf::Color(234, 234, 235);
                this->TEXT_COLOR = sf::Color(157, 157, 157);
                this->CONTENT_COLOR = sf::Color(68, 68, 68);
                this->HEIGHLIGHT = sf::Color(0, 0, 0, 50);
            }
    };
}

#endif