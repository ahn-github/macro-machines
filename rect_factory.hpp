#ifndef MM_RECT_FACTORY_H
#define MM_RECT_FACTORY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "entity.hpp"


namespace mm
{
    namespace Factories
    {
        class Rect
        {
        public:
            Entity* create(int id,
                           const sf::Vector2f pos,
                           const sf::Vector2f size,
                           b2World &world);
        };
    }
}

#endif
