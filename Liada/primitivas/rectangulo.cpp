#include "rectangulo.hpp"


RectanguloXZ::RectanguloXZ(double w, double h, 
    const Punto& o, const shared_ptr<BRDF>& brdf) 
    : Primitiva(brdf), 
      x0(o.getX() - w / 2), z0(o.getZ() - h / 2), x1(o.getX() + w / 2), z1(o.getZ() + h / 2), k(o.getY()) 
    {}

Interseccion RectanguloXZ::interseccion(const Rayo& r, double minT, double maxT) {
    Interseccion inter;

    //Solve for t
    double t = (k - r.getOrigen().getY()) / r.getDireccion().getY();

    // Verify if the plane not intersect behind of the r.origin
    if (t < minT + 0.001 || t > maxT) {
        inter.intersecta = false;
    }
    else {
        Punto ip = r(t);
        inter.intersecta = ip.getX() > x0 && ip.getX() < x1 && ip.getZ() > z0 && ip.getZ() < z1;
    }

    if (inter.intersecta) {
        inter.textura = brdf;
        inter.distancia = t;
        inter.normal = corregirNormal(r.getDireccion(), Direccion(0, 1, 0));
        auto [ u, v ] = getUVCoords(r(t));

        inter.u = u; 
        inter.v = v;
    }
    return inter;
}

tuple<double, double> RectanguloXZ::getUVCoords(const Punto& p) {
    return {(p.getX()-x0)/(x1-x0), (p.getZ()-z0)/(z1-z0)};
}




RectanguloXY::RectanguloXY(double w, double h, 
    const Punto& o, const shared_ptr<BRDF>& brdf) 
    : Primitiva(brdf), 
      x0(o.getX() - w / 2), y0(o.getY() - h / 2), x1(o.getX() + w / 2), y1(o.getY() + h / 2), k(o.getZ()) 
    {}

Interseccion RectanguloXY::interseccion(const Rayo& r, double minT, double maxT) {
    Interseccion inter;

    //Solve for t
    double t = (k - r.getOrigen().getZ()) / r.getDireccion().getZ();

    // Verify if the plane not intersect behind of the r.origin
    if (t < minT + 0.001  || t > maxT) {
        inter.intersecta = false;
    }
    else {
        Punto ip = r(t);
        inter.intersecta = ip.getX() > x0 && ip.getX() < x1 && ip.getY() > y0 && ip.getY() < y1;
    }

    if (inter.intersecta) {
        inter.textura = brdf;
        inter.distancia = t;
        inter.normal = corregirNormal(r.getDireccion(), Direccion(0, 0, 1));
        auto [ u, v ] = getUVCoords(r(t));

        inter.u = u; 
        inter.v = v;
    }
    return inter;
}

tuple<double, double> RectanguloXY::getUVCoords(const Punto& p) {
    return {(p.getX()-x0)/(x1-x0), (p.getY()-y0)/(y1-y0)};
}

RectanguloYZ::RectanguloYZ(double w, double h, 
    const Punto& o, const shared_ptr<BRDF>& brdf) 
    : Primitiva(brdf), 
      y0(o.getY() - w / 2), z0(o.getZ() - h / 2), y1(o.getY() + w / 2), z1(o.getZ() + h / 2), k(o.getX()) 
    {}

Interseccion RectanguloYZ::interseccion(const Rayo& r, double minT, double maxT) {
    Interseccion inter;

    //Solve for t
    double t = (k - r.getOrigen().getX()) / r.getDireccion().getX();

    // Verify if the plane not intersect behind of the r.origin
    if (t < minT + 0.001  || t > maxT) {
        inter.intersecta = false;
    }
    else {
        Punto ip = r(t);
        inter.intersecta = ip.getY() > y0 && ip.getY() < y1 && ip.getZ() > z0 && ip.getZ() < z1;
    }

    if (inter.intersecta) {
        inter.textura = brdf;
        inter.distancia = t;
        inter.normal = corregirNormal(r.getDireccion(), Direccion(1, 0, 0));
        auto [ u, v ] = getUVCoords(r(t));

        inter.u = u; 
        inter.v = v;
    }
    return inter;
}

tuple<double, double> RectanguloYZ::getUVCoords(const Punto& p) {
    return {(p.getY()-y0)/(y1-y0), (p.getZ()-z0)/(z1-z0)};
}