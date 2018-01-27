#ifndef MM_FACTORY_H
#define MM_FACTORY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>


namespace mm
{
  class Factory
  {
  public:
    void setWorld(b2World &world);
    void setTexture(sf::Texture &texture);

  protected:
    b2World *world_;
    sf::Texture *texture_;

    sf::RectangleShape* createRect(sf::Vector2f size, sf::Color color) const;

    b2Body* createDynamicBody(sf::Vector2f pos, sf::Vector2f size,
                             float32 linearDamping, float32 angularDamping,
                             float32 density, float32 friction, float32 = 0) const;

    b2Body* createStaticBody(sf::Vector2f pos, sf::Vector2f size) const;
  };
}

#endif
