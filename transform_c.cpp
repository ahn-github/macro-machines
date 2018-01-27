#include "transform_c.hpp"


namespace mm
{
    TransformC::TransformC() :
        sf::Transformable()
    {}

	TransformC::TransformC(float x, float y) :
		sf::Transformable()
    {
    	setPosition(x, y);
    }

    TransformC::TransformC(sf::Vector2f pos, sf::Vector2f origin) :
    	sf::Transformable()
    {
    	setOrigin(origin);
    	setPosition(pos);
    }
}
