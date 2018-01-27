#ifndef MM_AI_NODE_H
#define MM_AI_NODE_H

#include "node.hpp"
#include "input_c.hpp"
#include "keyboard_input_c.hpp"
#include "physics_c.hpp"

#include <cstdio>
#include <ctime>


namespace mm
{
	class AI : public Node
	{
	public:
		AI(Entity &entity) :
		Node(entity),
		input(entity.getComponent<KeyboardInputC>()),
		physics(entity.getComponent<PhysicsC>()),
		index(0),
		lastAngle(0.0f),
		start(0),
		duration(0),
		totError(0.0f)
		{}

		InputC &input;
		PhysicsC &physics;

		unsigned int index;
		float lastAngle;

		std::clock_t start;
		double duration;

		float totError;

	};
}

#endif
