#ifndef MM_CAR_SYSTEM_H
#define MM_CAR_SYSTEM_H

#include <iostream>
#include <Box2D/Box2D.h>

#include "system.hpp"
#include "car_node.hpp"


namespace mm
{
    //!
    /*!
     */
    class CarSystem : public System<CarNode>
    {
    public:
        virtual void update(float dt);

    private:
    };
}

#endif
