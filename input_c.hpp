#ifndef MM_INPUT_C_H
#define MM_INPUT_C_H

#include <Box2D/Box2D.h>

#include "component.hpp"


namespace mm
{
    //! Stores the current state of input of a vehicle
    class InputC : public Component
    {
    public:
        //! Input state, e.g. which (physical or virtual) arrow keys are pressed
        /*!
         * This is a struct because it's easy to overwrite.
         */
        typedef struct
        {
            bool forward;
            bool reverse;
            bool left;
            bool right;
            bool fire;
        } InputState;
        InputC() :
            state({false, false, false, false, false})
        {}
        virtual ~InputC() {};
        virtual void update() = 0;
        InputState state;
    };
}

#endif
