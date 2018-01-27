#include "factory.hpp"
#include "physics_c.hpp"


namespace mm
{
    void Factory::setWorld(b2World &world)
    {
        world_ = &world;
    }

    void Factory::setTexture(sf::Texture &texture)
    {
        texture_ = &texture;
    }

    sf::RectangleShape* Factory::createRect(sf::Vector2f size, sf::Color color)
        const
    {
        sf::RectangleShape *rect = new sf::RectangleShape(size);
        rect->setFillColor(color);
        return rect;
    }

    b2Body* Factory::createDynamicBody(sf::Vector2f pos, sf::Vector2f size,
                                       float32 linearDamping,
                                       float32 angularDamping, float32 density,
                                       float32 friction, float32 angle) const
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;;
        bodyDef.position.Set(pos.x/mm::PPM, pos.y/mm::PPM);
        bodyDef.linearDamping = linearDamping;
        bodyDef.angularDamping = angularDamping;
		bodyDef.angle = angle;

        b2PolygonShape shape;
        shape.SetAsBox(size.x/mm::PPM/2, size.y/mm::PPM/2);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = density;
        fixtureDef.friction = friction;

        b2Body *body = world_->CreateBody(&bodyDef);
        body->CreateFixture(&fixtureDef);

        return body;
    }

    b2Body* Factory::createStaticBody(sf::Vector2f pos, sf::Vector2f size) const
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(pos.x/mm::PPM, pos.y/mm::PPM);

        b2PolygonShape shape;
        shape.SetAsBox(size.x/mm::PPM/2, size.y/mm::PPM/2);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;

        b2Body *body = world_->CreateBody(&bodyDef);
        body->CreateFixture(&fixtureDef);

        return body;
    }
}
