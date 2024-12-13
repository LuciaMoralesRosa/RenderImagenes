#include "plano.hpp"

tuple<double, double> Plano::getUVCoords(const Punto& point) const {
    // UV coordinates on a plane are equal to the length of the projection
    // to the U and V parametric axes of the plane.
    Direccion p(point.getX(), point.getY(), point.getZ());
    return make_tuple<double, double>(productoEscalar(uAxis, p), productoEscalar(vAxis, p));
}

Interseccion Plano::interseccion(const Rayo& r, double minT, double maxT) {
    Interseccion inter;

    //Solve for t
    double t = -((c + productoEscalar(r.origin - Punto(0,0,0), normal)) / productoEscalar(r.direction, normal));

    // Verify if the plane not intersect behind of the r.origin
    if (t < minT + INTERSECTION_TOLERANCE || t > maxT) {
        inter.intersects = false;
    }
    else {
        inter.intersects = true;
    }

    if ( inter.intersects ) {
        inter.brdf = brdf;
        inter.intersections.emplace(t, normalizada(normal));
        auto [ u, v ] = getUVCoords(r(t));

        inter.u = u; 
        inter.v = v;
    }
    
    return inter;
}