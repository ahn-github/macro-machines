#ifndef MM_CONTACTLISTENER_H
#define MM_CONTACTLISTENER_H
#include <Box2D/Box2D.h>
#include <set>
#include "entity.hpp"

namespace mm
{
    class ContactListener : public b2ContactListener
    {
    public:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        bool getCarAndWeapon(b2Contact* contact, Entity*& carEntity, Entity*& weaponEntity);
        bool getCarAndGrass(b2Contact* contact, Entity*& carEntity);
        bool getCarAndCheckpoint(b2Contact* contact, Entity*& carEntity, Entity*& cpEntity);

        std::set<Entity*> getEntitiesToRemove();
        void clearEntitiesToRemove();
        int grassId = 501;
        int checkpointId = 666;
        int startLineId = 667;
    private:
        std::set<Entity*> entitiesToRemove_;
    };
}
#endif
