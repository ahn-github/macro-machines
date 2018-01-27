#ifndef MM_DRAW_NODE_H
#define MM_DRAW_NODE_H

#include "node.hpp"
#include "transform_c.hpp"
#include "drawable_c.hpp"


namespace mm
{
    class DrawNode : public Node
    {
    public:
        DrawNode(Entity &entity) :
            Node(entity),
            transform(entity.getComponent<TransformC>()),
            drawable(entity.getComponent<DrawableC>())
        {}

        TransformC &transform;
        DrawableC &drawable;
    };
}

#endif
