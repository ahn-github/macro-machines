#include "node.hpp"


namespace mm
{
    Node::Node(Entity &entity) :
        id_(entity.getId())
    {}

    int Node::getId() const
    {
        return id_;
    }
}
