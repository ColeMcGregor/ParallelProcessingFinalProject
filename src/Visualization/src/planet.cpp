#include "Planet.h"

Planet::Planet(double radius, double mass, Vector position, std::string type)
    : Body(radius, mass, position, type) {}
