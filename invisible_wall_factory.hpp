#ifndef MM_INVISIBLE_WALL_FACTORY_H
#define MM_INVISIBLE_WALL_FACTORY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <utility>

#include "factory.hpp"
#include "entity.hpp"


namespace mm
{
    namespace Factories
    {
        class InvisibleWall : public Factory
        {
        public:
			void create(sf::Vector2f pos, sf::Vector2f size) const;
        };
    }
}

#endif
