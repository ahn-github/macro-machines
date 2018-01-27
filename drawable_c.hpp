#ifndef MM_DRAWABLE_C_H
#define MM_DRAWABLE_C_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "component.hpp"


namespace mm
{
    class DrawableC : public Component
    {
    public:
        DrawableC(sf::Drawable *d) :
            drawable_(d)
        {}

        DrawableC(const DrawableC &other) :
            drawable_(other.drawable_)
        {}

        sf::Drawable& getDrawable()
        {
            return *drawable_;
        }

    private:
        std::shared_ptr<sf::Drawable> drawable_;
    };
}

#endif
