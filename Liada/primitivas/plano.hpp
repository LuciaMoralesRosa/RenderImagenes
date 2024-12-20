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
class Plano : public Primitiva {
    private:
    double distancia; // valor c
    Direccion normal, uAxis, vAxis;

    tuple<double, double> getUVCoords(const Punto& point) const;

public:
    
    Plano(Punto a, Punto b, Punto c, const shared_ptr<BRDF>& brdf)
        : Primitiva(brdf),
          normal(productoVectorial(b - a, c - a)),
          uAxis(b - a),
          vAxis(c - a),
          distancia(-productoEscalar(a - Punto(0,0,0), normal)) 
    {}

    /**
     * @brief Construct a new Plano with values
     * @param _c The value of c
     * @param _normal The value of the normal of the plane
     */
    Plano(double d, Direccion n, const shared_ptr<BRDF>& brdf) 
        : Primitiva(brdf),
          normal(n),
          uAxis(perpendicular(normal)), 
          vAxis(productoVectorial(normal, uAxis)),
          distancia(d)
    {}

    Interseccion interseccion(const Rayo& r, double minT = 0.001, double maxT = INFINITY) override;

    // Getters
    double getDistancia() const { return distancia; }
    Direccion getNormal() const { return normal; }

};