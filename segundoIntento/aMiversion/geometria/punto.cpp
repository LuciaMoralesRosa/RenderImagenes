#include "punto.hpp"

//------------------------------- CONSTRUCTORES ------------------------------//
Punto::Punto () : Vector(0, 0, 0, 1) {}

Punto::Punto (float x, float y, float z) : Vector(x, y, z, 1) {}

Punto::Punto (Vector v) : Vector(v.getX(), v.getY(), v.getZ(), 1) {}
//------------------------------- CONSTRUCTORES ------------------------------//


//----------------------------- METODOS PUBLICOS -----------------------------//
Vector obtenerVector(Punto p) {
    return Vector(p.getX(), p.getY(), p.getZ(), 1);
}
//----------------------------- METODOS PUBLICOS -----------------------------//


//-------------------------------- OPERADORES --------------------------------//
istream &operator>> (istream &i, Punto &p) {
    i >> p.x >> p.y >> p.z;
    return i;
}
//-------------------------------- OPERADORES --------------------------------//
