#include "plano.hpp"

tuple<double, double> Plano::getUVCoords(const Punto& point) const {
    // UV coordinates on a plane are equal to the length of the projection
    // to the U and V parametric axes of the plane.
    Direccion p(point.getX(), point.getY(), point.getZ());
    return make_tuple<double, double>(productoEscalar(uAxis, p), productoEscalar(vAxis, p));
}

Interseccion Plano::interseccion(const Rayo& r, double minT, double maxT) {
    Interseccion inter;

    Punto o = r.getOrigen();
    Direccion d = r.getDireccion();
    double t = -((distancia + productoEscalar(o - Punto(0,0,0), normal)) / productoEscalar(d, normal));

    // Comprobar si no intersecta por detras del origen
    if (t < minT + 0.0001 || t > maxT) {
        inter.intersecta = false;
        inter.punto = Punto();
        inter.distancia = 0;
    }
    else {
        inter.intersecta = true;
        inter.punto = Punto(o, d, t);
        inter.normal = normalizar(normal);
        inter.distancia = t;
        inter.textura = brdf;

        auto[u, v] = getUVCoords(r(t));
        inter.u = u; 
        inter.v = v;
    }
    
    return inter;
}