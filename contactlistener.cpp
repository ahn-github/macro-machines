#include <iostream>
#include "contactlistener.hpp"
#include "car_properties_c.hpp"
#include "weapon_c.hpp"
#include "physics_c.hpp"
#include "entity.hpp"

namespace mm
{
    void ContactListener::BeginContact(b2Contact* contact) {
        Entity* entityA;
        Entity* entityB;
        if (getCarAndWeapon(contact, entityA, entityB)) {
            // entityA is the car Entity*
            // entityB is the weapon Entity*

            //std::cout << "car " << entityA->getId() << " weapon " << entityB->getId() << "collided" << std::endl;
            auto carBody = entityA->getComponent<mm::PhysicsC>().body;
            switch (entityB->getComponent<mm::WeaponC>().type) {
            case mm::OILSPILL:
                std::cout << "car " << entityA->getId() << " ran over an oil slick!" << std::endl;
                //entityA->getComponent<mm::CarPropertiesC>().frontWheelDriftiness = 0.3f;
                //entityA->getComponent<mm::CarPropertiesC>().rearWheelDriftiness = 0.5f;
                carBody->ApplyAngularImpulse(7, true);
                break;
            case mm::BOOST:
                std::cout << "car " << entityA->getId() << " got a super boost!" << std::endl;
                carBody->ApplyLinearImpulse(4 * carBody->GetLinearVelocity(), carBody->GetWorldCenter(), true);
                //std::cout << "acceleration set to " << entityA->getComponent<mm::CarPropertiesC>().accelerationF << std::endl;
                break;
            case mm::BOMB:
                carBody->ApplyLinearImpulse(-3 * carBody->GetLinearVelocity(), carBody->GetWorldCenter(), true);
                //entityA->getComponent<mm::PhysicsC>().body->ApplyAngularImpulse(20, true);
                break;
            }
            entitiesToRemove_.insert(entityB);
        }
        else if (getCarAndGrass(contact, entityA)) {
            // entityA will become the car Entity*
            // when the function returns true
            //std::cout << "car on grass now" << std::endl;
            entityA->getComponent<mm::CarPropertiesC>().maxSpeed = 7.0f;
            entityA->getComponent<mm::CarPropertiesC>().collisioncounter += 1;
            //std::cout << entityA->getComponent<mm::CarPropertiesC>().collisioncounter << std::endl;
        }
        else if (getCarAndCheckpoint(contact, entityA, entityB)) {
            unsigned int &lapCounter = entityA->getComponent<mm::CarPropertiesC>().lapCounter;
            bool &checkpointPassed = entityA->getComponent<mm::CarPropertiesC>().checkpointPassed;
            if (checkpointPassed && entityB->getId() == startLineId) {
                lapCounter++;
                checkpointPassed = false;
                std::cout << entityA->getId() << ": lap " << lapCounter << std::endl;
            } else if (entityB->getId() == checkpointId) {
                checkpointPassed = true;
                std::cout << entityA->getId() <<  ": checkpoint passed" << std::endl;
            }
        }

    }
    void ContactListener::EndContact(b2Contact* contact) {
        Entity* entityA;
        if (getCarAndGrass(contact, entityA)) {
            entityA->getComponent<mm::CarPropertiesC>().collisioncounter -= 1;
            if (entityA->getComponent<mm::CarPropertiesC>().collisioncounter <= 0) {
                entityA->getComponent<mm::CarPropertiesC>().maxSpeed = 25.0f;
            }
        }

    }
    bool ContactListener::getCarAndWeapon(b2Contact* contact, Entity*& carEntity, Entity*& weaponEntity) {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();
        bool sensorA = fixtureA->IsSensor();
        bool sensorB = fixtureB->IsSensor();
        Entity* entityA = static_cast<Entity*>(fixtureA->GetBody()->GetUserData());
        Entity* entityB = static_cast<Entity*>(fixtureB->GetBody()->GetUserData());
        if (entityA == NULL || entityB == NULL) {
            //std::cout << "FIXME: someone did not have his userdata set; please get rid of this" << std::endl;
            // probably just remove the fixme if the invisible walls do not even have their entities and ids
            return false;
        }
        if (!(sensorA ^ sensorB) )
            // only one of the entities can possibly be sensors but double-checking is fun
            return false;
        if ((entityA->getId() % 10) != 0)
            // this is a lousy method of checking if the car entity is indeed a car
            return false;
        if (sensorA) {
            weaponEntity = entityA;
            carEntity = entityB;
            return true;
        }
        else {
            weaponEntity = entityB;
            carEntity = entityA;
            return true;
        }
        return false;

    }
    bool ContactListener::getCarAndGrass(b2Contact* contact, Entity*& carEntity) {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();
        bool sensorA = fixtureA->IsSensor();
        bool sensorB = fixtureB->IsSensor();
        Entity* entityA = static_cast<Entity*>(fixtureA->GetBody()->GetUserData());
        Entity* entityB = static_cast<Entity*>(fixtureB->GetBody()->GetUserData());
        if (entityA == NULL || entityB == NULL) {
            //std::cout << "FIXME: someone did not have his userdata set; please get rid of this" << std::endl;
            // probably just remove the fixme if the invisible walls do not even have their entities and ids
            return false;
        }
        if (!(sensorA ^ sensorB) )
            // only one of the entities can possibly be sensors but double-checking is fun
            return false;

        if ((entityB->getId() % 10) != 0) {
            // this is a lousy method of checking if the car entity is indeed a car
            return false;
        }

        if (entityA->getId() == grassId){
            carEntity = entityB;
            return true;
        }
        return false;
    }
    bool ContactListener::getCarAndCheckpoint(b2Contact* contact, Entity*& carEntity, Entity*& cpEntity) {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();
        bool sensorA = fixtureA->IsSensor();
        bool sensorB = fixtureB->IsSensor();
        Entity* entityA = static_cast<Entity*>(fixtureA->GetBody()->GetUserData());
        Entity* entityB = static_cast<Entity*>(fixtureB->GetBody()->GetUserData());
        if (entityA == NULL || entityB == NULL) {
            //std::cout << "FIXME: someone did not have his userdata set; please get rid of this" << std::endl;
            // probably just remove the fixme if the invisible walls do not even have their entities and ids
            return false;
        }
        if (!(sensorA ^ sensorB) )
            // only one of the entities can possibly be sensors but double-checking is fun
            return false;

        if ((entityB->getId() % 10) != 0) {
            // this is a lousy method of checking if the car entity is indeed a car
            return false;
        }

        if (entityA->getId() == checkpointId || entityA->getId() == checkpointId+1){
            carEntity = entityB;
            cpEntity = entityA;
            return true;
        }
        return false;
    }

    std::set<Entity*> ContactListener::getEntitiesToRemove() {
        return entitiesToRemove_;
    }
    void ContactListener::clearEntitiesToRemove() {
        entitiesToRemove_.clear();
    }
}
