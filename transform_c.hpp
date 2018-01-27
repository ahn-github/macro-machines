#ifndef MM_TRANSFORM_C_H
#define MM_TRANSFORM_C_H

#include <SFML/Graphics.hpp>

#include "component.hpp"


namespace mm
{
    //! Common transform component
    /*!
     * Zero angle and the x axis point to the right and the y axis points down
     * on the screen.
     */
    class TransformC : public Component, public sf::Transformable
    {
    public:
        TransformC();

        TransformC(float x, float y);

        TransformC(sf::Vector2f pos, sf::Vector2f origin = sf::Vector2f(0.f, 0.f));
    };
}

#endif
