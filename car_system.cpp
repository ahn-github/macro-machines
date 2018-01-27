#include "car_system.hpp"


namespace mm
{
    void CarSystem::update(float dt)
    {
        for(auto &node : nodes_) {
            b2Body *body = node.physics.body;
            auto &props = node.properties;
            auto &joints = node.wheels.joints;

            // Desired front wheel orientation
            float32 angleSetpoint;
            const float32 angleRange = mm::PI/5;
            if(node.input.state.left) {
                angleSetpoint = -angleRange;
            }
            else if(node.input.state.right) {
                angleSetpoint = angleRange;
            } else {
                angleSetpoint = 0;
            }

            // Step wheel angles to desired direction
            float32 currentAngle = joints[0]->GetJointAngle();
            const float32 angleStep = 0.05f;
            float32 newAngle;
            if(currentAngle < angleSetpoint)
                newAngle = currentAngle + angleStep;
            else if(currentAngle > angleSetpoint)
                newAngle = currentAngle - angleStep;
            else
                newAngle = 0.f;

            // Set wheel angles
            joints[0]->SetLimits(newAngle, newAngle);
            joints[1]->SetLimits(newAngle, newAngle);


            // Calculate velocity
            b2Vec2 fNormal(body->GetWorldVector(b2Vec2(0, 1)));
            b2Vec2 worldVel(b2Dot(fNormal, body->GetLinearVelocity()) * fNormal);
            b2Vec2 localVel(body->GetLocalVector(worldVel));

            // Acceleration, braking, and reversing
            float acceleration = 0.f;
            if(node.input.state.reverse) {
                if(localVel.y < 0.05) {
                    // Reverse
                    if(localVel.y > -props.maxReverseSpeed)
                        acceleration = -props.reverseF;
                }
                else {
                    // Brake
                    b2Body *body = node.physics.body;
                    body->SetLinearVelocity(props.brakingCoeff * body->GetLinearVelocity());
                    //acceleration = -props.brakingCoeff * localVel.y;
                }
            }
            else if(node.input.state.forward) {
                // Accelerate
                if(localVel.y < props.maxSpeed)
                    acceleration = props.accelerationF;
            }

            // Apply motor force
            body->ApplyForce(body->GetWorldVector(acceleration * b2Vec2(0, 1)),
                             body->GetWorldCenter() +
                             body->GetWorldVector(props.forcePoint),
                             true);

            std::array<float32, 2> driftiness =
                {{
                    node.properties.frontWheelDriftiness,
                    node.properties.rearWheelDriftiness
                }};
            size_t i = 0;
            for(auto wheelBody : node.wheels.bodies) {
                // Kill some of the lateral velocity of the wheels for somewhat
                // realistic turning
                b2Vec2 rNormal = wheelBody->GetWorldVector(b2Vec2(1, 0));
                b2Vec2 latVel = b2Dot(rNormal, wheelBody->GetLinearVelocity())
                                      * rNormal;
                b2Vec2 impulse = driftiness[(size_t)floor(i/2.0)] *
                    wheelBody->GetMass() * -latVel;
                wheelBody->ApplyLinearImpulse(impulse, wheelBody->GetWorldCenter(),
                                              true);
                ++i;
            }
        }
    }
}
