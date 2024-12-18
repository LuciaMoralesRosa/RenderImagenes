#include "esfera.hpp"

tuple<double, double> Esfera::getUVCoords(const Punto& point) const {

    // Get radius from center to point and compute inclination and azimuth
    // Adapted from https://raytracing.github.io/books/RayTracingTheNextWeek.html#imagetexturemapping/storingtextureimagedata

    double phi = atan2(point.getZ(), -point.getX()) + M_PI;
    double th  = acos(-point.getY());

    return make_tuple(phi, th);
}

Interseccion Esfera::interseccion(const Rayo& r, double minT, double maxT) {

    Interseccion inter;
    Direccion dif = r.getOrigen() - centro;
    inter.intersecta = false;

    double a = productoEscalar(r.getDireccion(), r.getDireccion());
    double halfb = productoEscalar(r.getDireccion(), dif);

    double c = productoEscalar(dif, dif) - radio * radio;

    // at^2 + bt + c = 0
    // Get discriminant
    double discr = halfb * halfb - a * c;

    // No hay raices reales -> no hay interseccion
    if (discr < 0.001) {
        return inter;
    }

    // Calcular puntos de interseccion
    double sq = sqrt(discr);
    // closest root
    double raiz1 = (-halfb - sq) / a;
    double raiz2 = (-halfb + sq) / a;
    
    if ( raiz1 < minT + 0.001 || maxT < raiz1 ) { 
        // Si la primera raiz esta fuera de rango
        if ( raiz2 < minT + 0.001 || maxT < raiz2 ) {
            // Si la segunda raiz esta fuera de rango
            return inter; // No hay interseccion
        }
        else {
            // La segunda raiz está en rango
            inter.distancia = raiz2;
            inter.normal = normalizar(r(raiz2) - centro);
            inter.punto = Punto(r.getOrigen(), r.getDireccion(), raiz2);
        }
    } else {
        // La raiz 1 es valida
        if ( raiz2 < minT + 0.001 || maxT < raiz2 ) {
            // Si la segunda raiz no es valida seguro que cojo la primera
            inter.distancia = raiz1;
            inter.normal = normalizar(r(raiz1) - centro);
            inter.punto = Punto(r.getOrigen(), r.getDireccion(), raiz1);
        }
        else {
            // Ambas raices son validas. Quiero la menor
            if(raiz1 < raiz2) {
                // La raiz 1 es menor que la raiz 2
                inter.distancia = raiz1;
                inter.normal = normalizar(r(raiz1) - centro);
                inter.punto = Punto(r.getOrigen(), r.getDireccion(), raiz1);    
            }
            else {
                // La raiz 2 es menor que la raiz 1
                inter.distancia = raiz2;
                inter.normal = normalizar(r(raiz2) - centro);
                inter.punto = Punto(r.getOrigen(), r.getDireccion(), raiz2);
            }
        }
    }

    inter.intersecta = true;
    inter.textura = brdf;
    auto [ u, v ] = getUVCoords(r(inter.distancia));

    inter.u = u; 
    inter.v = v;

    return inter;
}
