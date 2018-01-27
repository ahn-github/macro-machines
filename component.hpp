#ifndef MM_COMPONENT_H
#define MM_COMPONENT_H


namespace mm
{
    //! A component of which Entities are composed of.
    class Component
    {
    private:
        friend class Entity;
        
        //! Unique ID
        int entityId;
    };
}

#endif
