#ifndef MM_DRAW_SYSTEM_H
#define MM_DRAW_SYSTEM_H

#include <iostream>

#include "system.hpp"
#include "draw_node.hpp"



namespace mm
{
    class DrawSystem : public System<DrawNode>
    {
    public:
        DrawSystem(sf::RenderWindow &window);

        virtual void update(float dt); 

    private:
        sf::RenderWindow &window_;
        sf::Event event_;
	};
}

#endif
