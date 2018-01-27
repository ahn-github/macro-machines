#ifndef MM_CAR_WHEELS_C_H
#define MM_CAR_WHEELS_C_H

#include <Box2D/Box2D.h>
#include <array>

#include "component.hpp"


namespace mm
{
    class CarWheelsC : public Component
    {
    public:
        std::array<b2Body*, 4> bodies;
        std::array<b2RevoluteJoint*, 4> joints;
    };
}

#endif
