#include "weapon_factory.hpp"
#include "physics_c.hpp"
#include "transform_c.hpp"
#include "drawable_c.hpp"
#include "weapon_c.hpp"

namespace mm
{
    namespace Factories
    {
        Entity* Weapon::create(int id,
                             sf::Vector2f pos,
                             mm::weaponType type)
        {
            Entity *weapon = new Entity(id);

            sf::Vector2f size = sf::Vector2f(30,30);
            sf::Color color = sf::Color(255, 255, 255);
            sf::RectangleShape *rect = createRect(size, color);
            rect->setTexture(texture_);
            switch (type) {
                case mm::OILSPILL:
                    rect->setTextureRect(sf::IntRect(0, 0, 109, 95));
                    break;
                case mm::BOMB:
                    rect->setTextureRect(sf::IntRect(110,0,64,64));
                    break;
                case mm::BOOST:
                    rect->setTextureRect(sf::IntRect(100,65,96,96));
                    break;
            }

            weapon->addComponent(new DrawableC(rect));
            weapon->addComponent(new TransformC(sf::Vector2f(0.f, 0.f), size/2.f));

            PhysicsC *phys = new PhysicsC();
            phys->body = createStaticBody(pos,size);
            phys->body->SetUserData(weapon);
            phys->body->GetFixtureList()->SetSensor(true);
            weapon->addComponent(phys);

            WeaponC *weaponc = new WeaponC(type);
            weapon->addComponent(weaponc);
            return weapon;
        }
    }
}
