#include "rayo.hpp"

//------------------------------- CONSTRUCTORES ------------------------------//
Rayo::Rayo() {}

Rayo::Rayo(const Punto& p, const Direccion& d) : origen(p), direccion(d) {}
//------------------------------- CONSTRUCTORES ------------------------------//


//-------------------------------- OPERADORES --------------------------------//
Vector Rayo::operator()(float t) const {
    return origen + t * direccion;
}
//-------------------------------- OPERADORES --------------------------------//
