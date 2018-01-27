#include "car_factory.hpp"
#include "physics_c.hpp"
#include "transform_c.hpp"
#include "drawable_c.hpp"
#include "car_properties_c.hpp"
#include "keyboard_input_c.hpp"
#include "car_wheels_c.hpp"


namespace mm
{
    namespace Factories
    {
        std::array<Entity*, 5> Car::create(int id, sf::Vector2f pos,
                                           sf::Vector2f size,
                                           sf::Color color,
                                           sf::Vector2f wheelSize,
										   float32 angle) const
        {
            // Car chassis entity
            Entity *car = new Entity(id);

            // Car chassis graphic
            sf::RectangleShape *bodyRect = createRect(size, color);
            bodyRect->setTexture(texture_, true);
            // Basic components
            car->addComponent(new DrawableC(bodyRect));
            car->addComponent(new TransformC(sf::Vector2f(0.f, 0.f), size/2.f));

            // Car properties
            mm::CarPropertiesC *properties = new CarPropertiesC();
            properties->forcePoint = {0.f, size.y/2 * 0.8f/mm::PPM};
            properties->accelerationF = 20.f;
            properties->reverseF = 5.f;
            properties->brakingCoeff = 0.98f;
            properties->maxSpeed = 25.f;
            properties->maxReverseSpeed = 8.f;
            properties->frontWheelDriftiness = 0.8f;
            properties->rearWheelDriftiness = 0.8f;
            car->addComponent(properties);

            mm::PhysicsC *phys = new PhysicsC();
            phys->body = createDynamicBody(pos, size, 0.f, 0.f, 0.9f, 0.5f, angle);
            phys->body->SetUserData(car);
            car->addComponent(phys);

            // Calculate wheel positions
            sf::Vector2f wheelOffset(sf::Vector2f(size.x/2+wheelSize.x, size.y/2 * 0.6f));
            sf::Vector2f tireStartPos(pos + wheelOffset);
            sf::Transform trans;
            std::array<sf::Vector2f, 4> wheelPos;
            wheelPos[0] = wheelOffset;
            trans.translate(-2 * wheelOffset.x, 0.f);
            wheelPos[1] = trans * wheelOffset;
            trans.translate(0.f, -2 * wheelOffset.y);
            wheelPos[2] = trans * wheelOffset;
            trans.translate(2 * wheelOffset.x, 0.f);
            wheelPos[3] = trans * wheelOffset;

            std::array<std::array<float32, 2>, 4> wheelDamping =
                {{{15.f, 15.f}, {15.f, 15.f}, {15.f, 15.f}, {15.f, 15.f}}};

            // Create wheels
            std::array<Entity*, 4> wheels;
            for(size_t i = 0; i < 4; ++i) {
                    wheels[i] = createWheel(id+1+i, pos, wheelSize,
                                            wheelDamping[i][0],
                                            wheelDamping[i][1], angle);
            }

            // Store wheel physics data in a component
            CarWheelsC *wheelPhysData = new CarWheelsC();
            for(size_t i = 0; i < 4; ++i) {
                wheelPhysData->bodies[i] = wheels[i]->getComponent<PhysicsC>().body;
            }

            // Prepare the returned array
            std::array<Entity*, 5> parts;
            parts[0] = car;
            std::copy(wheels.begin(), wheels.end(), parts.begin() + 1);

            // Define wheel joints
            b2RevoluteJointDef jointDef;
            jointDef.bodyA = phys->body;
            jointDef.enableLimit = true;
            jointDef.lowerAngle = 0;
            jointDef.upperAngle = 0;
            jointDef.localAnchorB.SetZero();

            // Create joints
            for(size_t i = 1; i < parts.size(); ++i) {
                jointDef.bodyB = parts[i]->getComponent<PhysicsC>().body;
                jointDef.localAnchorA.Set(wheelPos[i-1].x/mm::PPM, wheelPos[i-1].y/mm::PPM);
                wheelPhysData->joints[i-1] = (b2RevoluteJoint*)world_->CreateJoint(&jointDef);
            }

            car->addComponent(wheelPhysData);

            return parts;
        }

        Entity* Car::createWheel(int id, sf::Vector2f pos, sf::Vector2f size,
                                 float32 linearDamping, float32 angularDamping, float32 angle)
            const
        {
            Entity *wheel = new Entity(id);

            sf::RectangleShape *wheelRect = createRect(size,
                                                      sf::Color(0, 0, 0));

            wheel->addComponent(new DrawableC(wheelRect));
            wheel->addComponent(new TransformC(sf::Vector2f(0.f, 0.f), size/2.f));

            mm::PhysicsC *phys = new PhysicsC();
            phys->body = createDynamicBody(pos, size, linearDamping,
                                           angularDamping, 0.4f, 0.7f, angle);
            phys->body->SetUserData(wheel);
            wheel->addComponent(phys);

            return wheel;
        }
    }
}
