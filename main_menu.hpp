#ifndef MM_MAIN_MENU_H
#define MM_MAIN_MENU_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>


namespace mm
{
    namespace MainMenu
    {
        typedef struct
        {
            size_t numAis;
            size_t numHumans;
            std::string mapName;
        } MenuChoices;

        MenuChoices display(sf::RenderWindow &window);
    };
}

#endif
