#include "ai_system.hpp"
#include "physics_c.hpp"


namespace mm
{
	void AISystem::update(float dt)
	{
		for (auto &node : nodes_) {

			InputC &input = node.input;
			PhysicsC &physics = node.physics;

			float rotation = physics.body->GetAngle() / M_PI * 180 + 90;
			sf::Vector2f position = sf::Vector2f(physics.body->GetPosition().x, physics.body->GetPosition().y);

			//Setting the checkpoint index
			if (waypoints[node.index].contains(sf::Vector2f(position.x * mm::PPM, position.y * mm::PPM))){
				++node.index;
				if (node.index == waypoints.size())
					node.index = 0;
			}
			
			//Calculating the next checkpoint's location
			sf::Vector2f checkPosition = sf::Vector2f((waypoints[node.index].left + waypoints[node.index].width / 2) / mm::PPM, (waypoints[node.index].top + waypoints[node.index].height / 2) / mm::PPM);

			//Vector from the car to the checkpoint
			float x = checkPosition.x - position.x;
			float y = checkPosition.y - position.y;

			//Getting the heading vector of the car (unit vector)
			float rot = static_cast<int>(rotation) % 360;

			float i = cos(rot / 180 * M_PI) * 180 / M_PI;
			float j = sin(rot / 180 * M_PI) * 180 / M_PI;

			sf::Vector2f heading = sf::Vector2f(i, j);

			//Values for dot product
			float dot = x * heading.x + y * heading.y;
			float det = x * heading.y - y * heading.x;

			//Calculating the angle
			float angle = atan2(det, dot) * 180 / M_PI;
			//std::cout << "angle:" << angle << std::endl;

			//PID Controller for the steering
			node.totError -= node.lastAngle;
			float control = angle * 0.23 + (angle - node.lastAngle) * 0.4 + node.totError * 0.025;
			const float maxControl = 3.0;
			node.lastAngle = angle;

			if (input.state.reverse == false){
				if (control > maxControl)
				{
					input.state.left = true;
					input.state.right = false;
				}

				else if (control < -maxControl)
				{
					input.state.left = false;
					input.state.right = true;
				}
				else{
					input.state.left = false;
					input.state.right = false;
					node.totError = 0;

				}
			}

			//Steering in the opposite direction if reversing
			else{
				if (control > maxControl)
				{
					input.state.left = false;
					input.state.right = true;
					node.totError = 0;
				}

				else if (control < -maxControl)
				{
					input.state.left = true;
					input.state.right = false;
					node.totError = 0;
				}
				else{
					input.state.left = false;
					input.state.right = true;
					node.totError = 0;
				}
			}
			
			//A simple logic for the "gas pedal"
			input.state.forward = !input.state.forward;

			//Calculating total velocity from the linear velocity components
			float totVelocity = std::sqrt(physics.body->GetLinearVelocity().x * physics.body->GetLinearVelocity().x + physics.body->GetLinearVelocity().y * physics.body->GetLinearVelocity().y);

			//Logic for reversing
			if (totVelocity < 0.7 && input.state.reverse == false){
				node.duration = (std::clock() - node.start) / (double)CLOCKS_PER_SEC;
				if (node.duration < 4){
					if (node.duration > 3){
						input.state.forward = false;
						input.state.reverse = true;
						node.start = std::clock();
					}
				}
				else{
					node.start = std::clock();
				}
				
			}
			else if (input.state.reverse == true){
				node.duration = (std::clock() - node.start) / (double)CLOCKS_PER_SEC;
				if (node.duration > 2){
					input.state.reverse = false;
					input.state.forward = true;
				}
			}
		}
	}
}
