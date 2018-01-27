#ifndef MM_NODE_H
#define MM_NODE_H

#include "entity.hpp"


namespace mm
{
    //! A node
    /*!
     * Nodes contain only the Components of an Entity a System is interested in.
     * This enables domain decoupling and using different kinds of entities with
     * the same system, as long as they contain the same subset of Components.
     *
     * Use private shared pointers for storing the Components. Accessor methods
     * should be named logically: for example, a method called test would return
     * a TestComponent.
     */
    class Node
    {
    public:
        //! Constructor
        Node(Entity &entity);

        //! Get the ID of the entity the Node was derived from
        int getId() const;

    protected:
        //! Original entity ID
        int id_;
    };
}

#endif
