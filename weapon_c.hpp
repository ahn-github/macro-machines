#ifndef MM_WEAPON_C_H
#define MM_WEAPON_C_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "component.hpp"


namespace mm
{
    enum weaponType {
        OILSPILL = 0,
        BOOST = 1,
        BOMB = 2,
    };
    class WeaponC : public Component
    {
    public:
        WeaponC(weaponType typ) :
            type(typ)
         {}
        WeaponC(weaponType typ, sf::Time time) :
            fireInterval(time),
            type(typ)
        {}
        sf::Time timeLastFired;
        sf::Time fireInterval;
        weaponType type;
    };
}

#endif
