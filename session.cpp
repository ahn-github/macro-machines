#include "session.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>

#include <vector>

#include "entity.hpp"
#include "transform_c.hpp"
#include "drawable_c.hpp"
#include "weapon_c.hpp"
#include "draw_system.hpp"
#include "physics_system.hpp"
#include "rect_factory.hpp"
#include "weapon_factory.hpp"
#include "car_system.hpp"
#include "keyboard_input_c.hpp"
#include "car_factory.hpp"
#include "ai_system.hpp"
#include "invisible_wall_factory.hpp"
#include "contactlistener.hpp"


namespace mm
{
	int Session::start(sf::RenderWindow &window, std::string mapName,
		size_t numPlayers, size_t numAiCars)
	{
		tmx::MapLoader mapLoader("maps/");
		mapLoader.Load(mapName);

		float angle = 0;
		if (mapName == "Snake2.tmx")
			angle = -mm::PI / 2;

		std::vector<sf::FloatRect> waypoints;
		sf::FloatRect tempRect;
		std::vector<sf::Vector2f> positions;

		mm::DrawSystem drawSys(window);
		mm::PhysicsSystem physSys(b2Vec2(0.f, 0.f));
		mm::CarSystem carSys;

		b2World &world = physSys.getWorld();
		mm::ContactListener cl;
		world.SetContactListener(&cl);

		for (auto &layer : mapLoader.GetLayers()) {
			if (layer.name == "Waypoint") {
				for (auto &object : layer.objects) {
					tempRect = object.GetAABB();
					waypoints.push_back(tempRect);
				}
			}

			if (layer.name == "Collision") {
				for (auto &object : layer.objects) {
					auto body = tmx::BodyCreator::Add(object, world, b2_staticBody);
					Entity *objectLayers = new Entity(601);
					body->SetUserData(objectLayers);
				}
			}

			if (layer.name == "Grass") {
				for (auto &object : layer.objects) {
					auto body = tmx::BodyCreator::Add(object, world, b2_staticBody);
					body->GetFixtureList()->SetSensor(true);
					Entity *objectLayers = new Entity(cl.grassId);
					body->SetUserData(objectLayers);
				}
			}

			if (layer.name == "Checkpoints") {
				unsigned int idCounter = 0;
				for (auto &object : layer.objects) {
					auto body = tmx::BodyCreator::Add(object, world, b2_staticBody);
					body->GetFixtureList()->SetSensor(true);
					Entity *objectLayers = new Entity(cl.checkpointId + idCounter);
					body->SetUserData(objectLayers);
					idCounter++;
				}
			}

			if (layer.name == "Start"){
				for (auto &object : layer.objects) {
					tempRect = object.GetAABB();
					positions.push_back(sf::Vector2f(tempRect.left + tempRect.width / 2, tempRect.top + tempRect.height / 2));
				}
			}
		}

		mm::AISystem aiSys(waypoints);

		const sf::Vector2f carSize(20, 40);
		const sf::Vector2f wheelSize(3, 8);

		mm::Factories::Car carFact;
		carFact.setWorld(world);
		sf::Texture cartexture;
		cartexture.loadFromFile("maps/redcar.png");
		carFact.setTexture(cartexture);
		mm::Factories::Weapon weaponFact;
		weaponFact.setWorld(world);
		sf::Texture weapontexture;
		weapontexture.loadFromFile("maps/weapon.png");
		weaponFact.setTexture(weapontexture);

		std::array<mm::InputC*, 2> playerInput = { nullptr, nullptr };
		std::array<mm::Entity*, 2> players = { nullptr, nullptr };
		std::vector<mm::Entity*> ais;

		// Create cars
		for (size_t i = 0; i < positions.size() && i < numPlayers + numAiCars; ++i) {
			//std::cout << i << std::endl;
			// Create entities
			std::array<mm::Entity*, 5> car =
				carFact.create(40 + i * 10, positions[i], carSize,
				sf::Color(255, 255, 255), wheelSize, angle);

			car[0]->addComponent(new mm::WeaponC(mm::OILSPILL, sf::seconds(1)));
			if (i < numPlayers) {
				// Car is human controlled
				car[0]->addComponent(new KeyboardInputC(i));
				playerInput[i] = &car[0]->getComponent<mm::KeyboardInputC>();
				players[i] = car[0];
				//std::cout << car[0] << std::endl;
			}
			else {
				car[0]->addComponent(new KeyboardInputC(-1));
				ais.push_back(car[0]);
				// Car is AI controlled
				aiSys.addEntity(*car[0]);
			}
			// Add entities to systems
			for (auto part : car) {
				drawSys.addEntity(*part);
				physSys.addEntity(*part);
			}
			carSys.addEntity(*car[0]);
		}

		unsigned int idCounter = 100;

		sf::Clock gameclock;

		while (window.isOpen()) {

			for (size_t i = 0; i < numPlayers; ++i) {
				playerInput[i]->update();
				mm::PhysicsC &physc = players[i]->getComponent<mm::PhysicsC>();
				mm::WeaponC &weaponc = players[i]->getComponent<mm::WeaponC>();
				unsigned int &lapCounter = players[i]->getComponent<mm::CarPropertiesC>().lapCounter;
				if (lapCounter >= 3)
						return 1;
				if (playerInput[i]->state.fire && weaponc.timeLastFired < gameclock.getElapsedTime() - weaponc.fireInterval) {
					auto point = physc.body->GetPosition();
					auto vec = physc.body->GetLinearVelocity();
					vec.Normalize();
					point -= 1.5*vec;
					point.x *= mm::PPM;
					point.y *= mm::PPM;
					//std::cout << vec.x << " " << vec.y << std::endl;
					mm::Entity* tmp = weaponFact.create(idCounter, sf::Vector2f(point.x, point.y), weaponc.type);
					drawSys.addEntity(*tmp);
					physSys.addEntity(*tmp);
					weaponc.timeLastFired = gameclock.getElapsedTime();
					std::cout << "weapon id " << idCounter << " of type " << weaponc.type << " fired by " << players[i]->getId() << " at " << gameclock.getElapsedTime().asSeconds() << "s" << std::endl;
					point.x = 0;
					point.y = 0;
					idCounter++;
					int weapontype = static_cast<int>(gameclock.getElapsedTime().asSeconds()) % 3;
					// pseudo-random way of testing different weapons
					weaponc.type = static_cast<mm::weaponType>(weapontype);
				}
			}

			for (size_t i = 0; i < ais.size(); ++i) {
				unsigned int &lapCounter = ais[i]->getComponent<mm::CarPropertiesC>().lapCounter;
				if (lapCounter >= 3)
					return 0;
			}

			auto removables = cl.getEntitiesToRemove();
			for (auto it = removables.begin(); it != removables.end(); it++) {
				Entity* removeThis = *it;
				drawSys.removeEntity(*removeThis);
				physSys.removeEntity(*removeThis);
				auto *body = removeThis->getComponent<mm::PhysicsC>().body;
				world.DestroyBody(body);

				delete removeThis;
				//std::cout << (*it)->getId() << std::endl;
			}
			cl.clearEntitiesToRemove();

			aiSys.update(1);
			carSys.update(1);
			physSys.update(1);
			window.clear();
			mapLoader.Draw(window, 0);
			drawSys.update(1);
			window.display();
		}
		return 1;
	}
}
