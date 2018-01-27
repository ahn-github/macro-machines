#define _USE_MATH_DEFINES

#ifndef MM_AI_SYSTEM_H
#define MM_AI_SYSTEM_H

#include <iostream>
#include <cstdio>
#include <ctime>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "system.hpp"
#include "ai_node.hpp"


namespace mm
{
	class AISystem : public System<AI>
	{
	public:
		AISystem(std::vector<sf::FloatRect> wp) :
			waypoints(wp)
		{}

		virtual void update(float dt);

	private:
		std::vector<sf::FloatRect> waypoints;
	};
}

#endif
