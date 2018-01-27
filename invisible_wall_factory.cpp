#include "invisible_wall_factory.hpp"
#include "physics_c.hpp"


namespace mm
{
    namespace Factories
    {
        void InvisibleWall::create(sf::Vector2f pos, sf::Vector2f size)
            const
        {
            createStaticBody(pos, size);
        }
    }
}
