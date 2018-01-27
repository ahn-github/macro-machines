#ifndef MM_ENTITY_H
#define MM_ENTITY_H

#include <stdexcept>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <cstdio>
#include <stdio.h>

#include "component.hpp"


namespace mm
{
    //! A component based entity
    /*!
     * Even though components and systems could be used without a separate
     * entity class, this makes fetching components easy.
     *
     * Warning: Make sure to remove any nodes from systems that hold references
     * to components in this entity before this entity is destroyed.
     */
    class Entity
    {
    public:
        //! Constructor
        /*!
         * \param id An arbitrary entity ID.
         */
        Entity(int id);

        //! Get the entity ID
        /*! \return The ID of the entity.
         */
        int getId() const;

        //! Add a component
        /*!
         * \param *c A pointer to the component to be added.
         */
        template<typename T>
        void addComponent(T *c)
        {
            c->entityId = id_;
            components_[std::type_index(typeid(*c))] = std::shared_ptr<T>(c);
        }

        //! Get a component
        /*!
         * A std::logic_error will be thrown if the component does not exist.
         *
         * \param T The type of the component to be fetched.
         * \return A reference to the component.
         */
        template<typename T>
        T& getComponent()
        {
            std::type_index i(typeid(T));
            if(components_.count(std::type_index(typeid(T))) != 0)
                return *std::static_pointer_cast<T>(components_[i]);
            else {
                char err[128];
                snprintf(err, 128, "Fatal: No such component in entity id %d: %s",
                    id_, typeid(T).name());
                throw std::logic_error(err);
            }
        }

        //Entity clone(int id);

    private:
        //! Unique ID
        int id_;

        //! An unordered map of the components, keyed by the component type
        std::unordered_map<std::type_index, std::shared_ptr<Component>>
            components_;
    };

    bool operator==(const Entity& l, const Entity& r);

    bool operator==(const Entity& l, int r);
}

#endif
