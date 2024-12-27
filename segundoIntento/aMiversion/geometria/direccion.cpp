#include "direccion.hpp"

//------------------------------- CONSTRUCTORES ------------------------------//
Direccion::Direccion () : Vector(0, 0, 0, 0) {}

Direccion::Direccion (float x, float y, float z) : Vector(x, y, z, 0) {}

Direccion::Direccion (Vector v) : Vector(v.getX(), v.getY(), v.getZ(), 0) {}
//------------------------------- CONSTRUCTORES ------------------------------//


//----------------------------- METODOS PUBLICOS -----------------------------//
Vector obtenerVector (Direccion d) {
    return Vector(d.getX(), d.getY(), d.getZ(), 0);
}

Direccion Direccion::direccionAleatoria() {
    double x = randTheta2.get(), y = randTheta2.get(), z = randTheta2.get();
    while (x*x + y*y + z*z > 1) {
        x = randTheta2.get();
        y = randTheta2.get();
        z = randTheta2.get();
    }
    return Direccion(x, y, z).normalizar();
}
//----------------------------- METODOS PUBLICOS -----------------------------//


//-------------------------------- OPERADORES --------------------------------//
istream &operator>> (istream &i, Direccion &d) {
    i >> d.x >> d.y >> d.z;
    return i;
}
//-------------------------------- OPERADORES --------------------------------//