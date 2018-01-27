#ifndef MM_PHYSICS_NODE_H
#define MM_PHYSICS_NODE_H

#include "node.hpp"
#include "transform_c.hpp"
#include "physics_c.hpp"


namespace mm
{
    class PhysicsNode : public Node
    {
    public:
        PhysicsNode(Entity &entity) :
            Node(entity),
            transform(entity.getComponent<TransformC>()),
            physics(entity.getComponent<PhysicsC>())
        {}

        TransformC &transform;
        PhysicsC &physics;
    };
}

#endif
