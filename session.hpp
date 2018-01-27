#ifndef MM_SESSION_H
#define MM_SESSION_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>


namespace mm
{
    namespace Session
    {
        int start(sf::RenderWindow &window, std::string mapName,
                   size_t numPlayers, size_t numAiCars);
    };
}

#endif
