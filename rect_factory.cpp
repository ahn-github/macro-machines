#include "rect_factory.hpp"
#include "physics_c.hpp"
#include "transform_c.hpp"
#include "drawable_c.hpp"


namespace mm
{
    namespace Factories
    {
        Entity* Rect::create(int id,
                             sf::Vector2f pos,
                             sf::Vector2f size,
                             b2World &world)
        {
            Entity *e = new Entity(id);

            sf::RectangleShape *rect = new sf::RectangleShape(size);
            rect->setFillColor(sf::Color::Transparent);
            e->addComponent(new DrawableC(rect));
            e->addComponent(new TransformC(sf::Vector2f(0.f, 0.f), size/2.f));

            PhysicsC *phys = new PhysicsC();
            b2BodyDef bodyDef;
            bodyDef.type = b2_dynamicBody;
            bodyDef.position.Set(pos.x/mm::PPM, pos.y/mm::PPM);
            bodyDef.linearDamping = 2.f;
            bodyDef.angularDamping = 2.5f;
            b2PolygonShape shape;
            shape.SetAsBox(size.x/mm::PPM/2, size.y/mm::PPM/2);
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &shape;
            fixtureDef.density = 0.3f;
            fixtureDef.friction = 0.5f;
            fixtureDef.filter.categoryBits = mm::WALL;
            // this is a wall
            fixtureDef.filter.maskBits = mm::CAR | mm::WALL;
            // it will collide with other cars
            phys->body = world.CreateBody(&bodyDef);
            phys->body->CreateFixture(&fixtureDef);
            e->addComponent(phys);

            return e;
        }
    }
}
