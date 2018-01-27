#ifndef MM_CAR_PROPERTIES_C_H
#define MM_CAR_PROPERTIES_C_H

#include <Box2D/Box2D.h>

#include "component.hpp"


namespace mm
{
    class CarPropertiesC : public Component
    {
    public:
        CarPropertiesC() :
            forcePoint(0.f, 0.f),
            accelerationF(50.f),
            reverseF(25.f),
            brakingCoeff(5.f),
            maxSpeed(15.f),
            maxReverseSpeed(7.f),
            frontWheelDriftiness(0.f),
            rearWheelDriftiness(0.f),
            collisioncounter(0.f),
            lapCounter(0),
            checkpointPassed(false)
        {}

        //! The local point where the steering force should be applied
        b2Vec2 forcePoint;
        //! Acceleration force (positive)
        float accelerationF;
        //! Reverse acceleration force
        float reverseF;
        //! Braking coefficient
        float brakingCoeff;
        //! Top speed
        float maxSpeed;
        //! Top reverse speed (positive)
        float maxReverseSpeed;
        //! Front wheel "driftiness"
        /*!
         * 1.0 = no drif, 0 = spaceship-like steering
         */
        float frontWheelDriftiness;
        //! Real wheel "driftiness"
        /*!
         * 1.0 = no drif, 0 = spaceship-like steering
         */
        float rearWheelDriftiness;

        float collisioncounter;
        unsigned int lapCounter;
        bool checkpointPassed;
    };
}

#endif
