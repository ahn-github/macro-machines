#ifndef MM_TEST_C_H
#define MM_TEST_C_H

#include <iostream>

#include "component.hpp"


namespace mm
{
    class TestC : public Component
    {
    public:
        void yee()
        {
            std::cout << "yee!" << std::endl;
        }
    };
}

#endif
