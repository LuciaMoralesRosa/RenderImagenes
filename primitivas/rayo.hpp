#pragma once

#include "../geometria/Direccion.hpp"
#include "../geometria/Punto.hpp"

using namespace std;

class Rayo {
    Punto origen;
    Direccion direccion;
    public:

    Rayo(Punto o, Direccion d) : origen(o), direccion(d.normalizada()) {}
    Rayo(Punto o, Punto d) : origen(o), direccion((d-o).normalizada()) {}


    inline Punto evaluar(double t) const { return origen + direccion * t; }
    inline Punto operator()(double t) const { return evaluar(t); }

    // Getters
    Punto getOrigen() const { return origen; }
    Direccion getDireccion() const { return direccion; }

};

/**
 * @brief Ajusta la normal de una superficie para asegurarse de que apunte hacia el rayo.
 *
 * Dada la dirección de un rayo y la normal de una superficie, esta función 
 * determina la orientación de la normal que debe apuntar en dirección opuesta al rayo. 
 * Si la normal ya está orientada correctamente, permanece sin cambios. 
 * De lo contrario, la normal se invierte.
 *
 * @param rdir La dirección del rayo (un Vector3).
 * @param n La normal de la superficie en el punto de intersección (un Vector3).
 * @return Vector3 La normal ajustada, orientada para apuntar en dirección opuesta al rayo.
 */
Direccion corregirNormal(const Direccion& rdir, const Direccion& n);

ostream& operator<<(ostream& os, const Rayo& r);