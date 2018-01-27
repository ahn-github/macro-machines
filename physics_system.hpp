#ifndef MM_PHYSICS_SYSTEM_H
#define MM_PHYSICS_SYSTEM_H

#include <iostream>
#include <Box2D/Box2D.h>

#include "system.hpp"
#include "physics_node.hpp"


namespace mm
{
    //! Box2D integration
    /*!
     * Steps the physics simulation and applies the resulting transformations to
     * entities.
     */
    class PhysicsSystem : public System<PhysicsNode>
    {
    public:
        PhysicsSystem(b2Vec2 gravity = b2Vec2(0.f, 0.f)) :
            world_(gravity)
        {}

        virtual void update(float dt);

        void addEntity(Entity &e);

        b2World& getWorld();

    private:
        b2World world_;
    };
}

#endif
