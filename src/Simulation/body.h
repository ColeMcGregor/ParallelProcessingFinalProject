#ifndef BODY_H
#define BODY_H

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "vector.h"

class Body
{
public:
        Vector position;     // where the body is
        Vector velocity;     // how fast it is moving in a given direction
        Vector acceleration; // how fast it is accelerating in a given direction
        Vector net_force;    // the net force acting on the body
        double mass;         // how much stuff it is made of
        double radius;       // how big it is from center to edge
        // special variables
        double gravitationalMultiplier;   // allows for different multiples of gravitational constants to see the effects of universal gravity scaling
        std::string type;                 // what type of body it is(moon, planet, star, blackhole)
        std::vector<int> childrenIndices; // the indices of the bodies that are children of this body
        std::vector<Vector> trajectory;   // the trajectory of the body through time

        Body(const Vector &pos,
             const Vector &vel,
             const Vector &accel,
             const Vector &net_force,
             const double mass,
             const double radius,
             const double gravitationalMultiplier,
             const std::string &type,
             const std::vector<int> &childrenIndices,
             std::vector<Vector> &trajectory);

        Vector gravForce(const Body &p2) const;
        void applyForce(const Vector &force);
        void update(double timestep);
        Vector sumForces(const std::vector<Body> &bodies);
        void printState() const;
};

#endif