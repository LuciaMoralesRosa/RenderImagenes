#include "luz.hpp" 
#include <random>
#include <functional>

Rayo LuzPuntual::sample() const {
    //TODO: add sampling distribution for each light type
    RandomGenerator rng(0, 1);
    double invTheta = acos(2 * rng() - 1);
    double invPhi = 2.0 * M_PI * rng();

    Direccion omega = Direccion(
        sin(invTheta) * cos(invPhi),
        sin(invTheta) * sin(invPhi),
        cos(invTheta)).normalizada();

    return Rayo(centro, omega);
}