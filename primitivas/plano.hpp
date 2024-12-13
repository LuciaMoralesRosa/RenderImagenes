#pragma once

#include <iostream>

#include "primitiva.hpp"
#include "../geometria/vector.hpp"
#include "../geometria/Direccion.hpp"
#include "../geometria/Punto.hpp"
#include "interseccion.hpp"

using namespace std;

/**
 * @brief Class for representing Planes
 * 
 */
class Plano : public Primitiva {
    private:
    double c;

    tuple<double, double> getUVCoords(const Punto& point) const;

public:
    Direccion normal, uAxis, vAxis;
    
    Plano(Punto _pointA, Punto _pointB, Punto _pointC, const shared_ptr<BRDF>& brdf)
        : Primitiva(brdf),
          normal(productoVectorial(_pointB - _pointA, _pointC - _pointA)),
          uAxis(_pointB - _pointA),
          vAxis(_pointC - _pointA),
          c(-productoEscalar(_pointA - Punto(0,0,0), normal)) 
    {}

    /**
     * @brief Construct a new Plano with values
     * @param _c The value of c
     * @param _normal The value of the normal of the plane
     */
    Plano(double _c, Direccion _normal, const shared_ptr<BRDF>& brdf) 
        : Primitiva(brdf),
          normal(_normal),
          uAxis(perpendicular(normal)), 
          vAxis(productoVectorial(normal, uAxis)),
          c(_c)
    {}

    Interseccion interseccion(const Rayo& r, double minT, double maxT) override;

};