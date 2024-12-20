#pragma once

#include <iostream>

#include "primitiva.hpp"
#include "../geometria/vector.hpp"
#include "../geometria/Direccion.hpp"
#include "../geometria/Punto.hpp"
#include "interseccion.hpp"
#include "rayo.hpp"

using namespace std;

/**
 * @brief Class for representing Planes
 * 
 */
class Esfera : public Primitiva {
    private:
    double radio;
    Punto centro;

    tuple<double, double> getUVCoords(const Punto& point) const;

public:
    
    Esfera(Punto c, double r, const shared_ptr<BRDF>& brdf)
        : Primitiva(brdf), centro(c), radio(r) {}


    Interseccion interseccion(const Rayo& r, double minT = 0.001, double maxT = INFINITY) override;

    // Getters
    double getRadio() const { return radio; }
    Punto getCentro() const { return centro; }

};