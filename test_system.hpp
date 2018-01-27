#ifndef MM_TEST_SYSTEM_H
#define MM_TEST_SYSTEM_H

#include <iostream>

#include "system.hpp"
#include "test_node.hpp"


namespace mm
{
    class TestSystem : public System<TestNode>
    {
    public:
        virtual void update(float dt)
        {
            for(auto &node : nodes_) {
                node.transform.rotate(5);
                //std::cout << node.transform()->getRotation() << std::endl;
                //node.test()->yee();
            }
        }
    };
}

#endif
