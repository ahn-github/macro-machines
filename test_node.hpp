#ifndef MM_TEST_NODE_H
#define MM_TEST_NODE_H

#include "node.hpp"
#include "transform_c.hpp"
#include "test_c.hpp"


namespace mm
{
    class TestNode : public Node
    {
    public:
        TestNode(Entity &entity) :
            Node(entity),
            transform(entity.getComponent<TransformC>()),
            test(entity.getComponent<TestC>())
        {}
        
        TransformC &transform;
        TestC &test;
    };
}

#endif
