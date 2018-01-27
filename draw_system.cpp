#include "draw_system.hpp"

#include <tmx/MapLoader.h>
#include <sstream>
#include <cassert>


namespace mm
{
	//Git works, gimppa was here
	DrawSystem::DrawSystem(sf::RenderWindow &window) :
        window_(window)
	{
	}

	void DrawSystem::update(float dt)
    {
        while (window_.pollEvent(event_)) {
            if (event_.type == sf::Event::Closed) window_.close();
            if (event_.type == sf::Event::KeyPressed) {
                // such convenience while testing this
                if (event_.key.code == sf::Keyboard::Escape) window_.close();
            }
        }

        for(auto &node : nodes_) {
            window_.draw(node.drawable.getDrawable(), node.transform.getTransform());
        }
    }
}
