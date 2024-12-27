#include "camara.hpp"

//------------------------------- CONSTRUCTORES ------------------------------//
Camara::Camara () {}

Camara::Camara (const Punto& origen, const Direccion& left, const Direccion& up,
    const Direccion& forward, int b, int a) : o(origen), l(left), u(up),
    f(forward), base(b), altura(a),
    basePixel(2*left.modulo() / b),
    alturaPixel(2*up.modulo() / a) {

    // Checks if the vectors are perpendicular.
    if (escalar(l, u) != 0 || escalar(l, f) != 0 || escalar(u, f) != 0) {
        throw "Los vectores l, u y f no son perpendiculares.";
    }
}
//------------------------------- CONSTRUCTORES ------------------------------//
