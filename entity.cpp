#include "entity.hpp"


namespace mm
{
    Entity::Entity(int id) :
        id_(id)
    {}

    int Entity::getId() const
    {
        return id_;
    }

    /*
    Entity Entity::clone(int id)
    {
        Entity newEntity(id);
        for(auto it = components_.cbegin(); it != components_.end(); ++it) {
            newEntity.components_[it->first] = new Component(*(it->second));
        }
        //newEntity.components_.insert(components_.begin(), components_.end());
        return newEntity;
    }
    */

    bool operator==(const Entity& l, const Entity& r)
    {
        return l.getId() == r.getId();
    }

    bool operator==(const Entity& l, int r)
    {
        return l.getId() == r;
    }
}
