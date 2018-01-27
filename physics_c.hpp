#ifndef MM_PHYSICS_C_H
#define MM_PHYSICS_C_H

#include <Box2D/Box2D.h>

#include "component.hpp"


namespace mm
{
    const float PPM = 30.f;
    const float PI = 3.1415927;
    enum entityCategory {
        WALL = 0x001,
        CAR = 0x002,
        WEAPON = 0x004,
    };

    class PhysicsC : public Component
    {
    public:
        b2Body *body;
    };
}

#endif
