#ifndef MM_WEAPON_FACTORY_H
#define MM_WEAPON_FACTORY_H

#include <SFML/Graphics.hpp>

#include "factory.hpp"
#include "entity.hpp"
#include "weapon_c.hpp"


namespace mm
{
    namespace Factories
    {
        class Weapon : public Factory
        {
        public:
            Entity* create(int id, const sf::Vector2f pos, weaponType type);
        };

    }
}

#endif
