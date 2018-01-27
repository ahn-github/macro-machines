#ifndef MM_CAR_NODE_H
#define MM_CAR_NODE_H

#include "node.hpp"
#include "input_c.hpp"
#include "keyboard_input_c.hpp"
#include "physics_c.hpp"
#include "car_properties_c.hpp"
#include "car_wheels_c.hpp"


namespace mm
{
    class CarNode : public Node
    {
    public:
        CarNode(Entity &entity) :
            Node(entity),
            input(entity.getComponent<KeyboardInputC>()),
            physics(entity.getComponent<PhysicsC>()),
            properties(entity.getComponent<CarPropertiesC>()),
            wheels(entity.getComponent<CarWheelsC>())
        {}

        InputC &input;
        PhysicsC &physics;
        CarPropertiesC &properties;
        CarWheelsC &wheels;
    };
}

#endif
