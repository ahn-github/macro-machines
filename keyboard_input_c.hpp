#ifndef MM_KEYBOARD_C_H
#define MM_KEYBOARD_C_H

#include "input_c.hpp"


namespace mm
{
    //! Stores the current state of input of a vehicle
    class KeyboardInputC : public InputC
    {
    public:
        //! Input state, e.g. which (physical or virtual) arrow keys are pressed
        /*!
         * This is a struct because it's easy to overwrite.
         */
        KeyboardInputC(unsigned int keymap) : InputC(), keys(keymap) { }
        void update();

		unsigned int keys;
    };
}

#endif
