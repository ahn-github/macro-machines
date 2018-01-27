#ifndef MM_SYSTEM_H
#define MM_SYSTEM_H

#include <list>

#include "entity.hpp"


namespace mm
{
    //! An interface for systems that add logic to Entities
    /*!
     * Systems hold a list of Nodes. using the data held by them. This enables domain
     * decoupling and using different kinds of entities with the same system.
     *
     * Usage example:
     *
     * class TestSystem : public System<TestNode> {...}
     *
     * \param T a node type
     */
    template<typename T>
    class System
    {
    public:
        //! Update system state
        /*!
         * \param dt time step in seconds
         */
        virtual void update(float dt) = 0;

        //! Construct a node from the entity
        /*!
         * \param &e an entity
         */
        void addEntity(Entity &e)
        {
            nodes_.push_back(T(e));
        }

        //! Remove entities by Entity reference
        /*!
         * \param &e an entity
         */
        void removeEntity(Entity &e)
        {
            removeEntity(e.getId());
        }

        //! Remove entities by ID
        /*!
         * \param id entity ID
         */
        void removeEntity(int id)
        {
            nodes_.remove_if([id](T node)
            {
                return node.getId() == id;
            });
        }

    protected:
        //! A list of nodes
        std::list<T> nodes_;
    };
}

#endif
