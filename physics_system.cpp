#include "physics_system.hpp"


namespace mm
{
	void PhysicsSystem::update(float dt)
    {
        world_.Step(1.f/60.f, 8, 3);
        world_.ClearForces();
        b2Vec2 pos;
        float angle;
        for(auto &node : nodes_) {
            pos = node.physics.body->GetPosition();
            angle = node.physics.body->GetAngle();
            node.transform.setPosition(pos.x*PPM, pos.y*PPM);
            node.transform.setRotation(angle*180/PI);
        }
    }

    void PhysicsSystem::addEntity(Entity &e)
    {
        System<PhysicsNode>::addEntity(e);
    }

    b2World& PhysicsSystem::getWorld()
    {
        return world_;
    }
}
