#ifndef MM_CAR_FACTORY_H
#define MM_CAR_FACTORY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <utility>

#include "factory.hpp"
#include "entity.hpp"


namespace mm
{
    namespace Factories
    {
        class Car : public Factory
        {
        public:
          std::array<Entity*, 5> create(int id, sf::Vector2f pos,
                                        sf::Vector2f size,
                                        sf::Color color,
                                        sf::Vector2f tireSize,
										float32 angle) const;

        private:
          Entity* createWheel(int id, sf::Vector2f pos, sf::Vector2f size,
                              float32 linearDamping, float32 angularDamping, float32 angle)
            const;
        };
    }
}

#endif
