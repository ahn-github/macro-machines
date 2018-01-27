#include <SFML/Graphics.hpp>

#include "keyboard_input_c.hpp"


namespace mm
{
    void KeyboardInputC::update() {
        switch (keys) {
        case 0:
            state =
            {
                .forward = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W),
                .reverse = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S),
                .left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A),
                .right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D),
                .fire = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q),
            };
            break;
            
        case 1:
            state =
            {
                .forward = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I),
                .reverse = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K),
                .left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J),
                .right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L),
                .fire = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U),
            };
            break;
        }
    }
}
