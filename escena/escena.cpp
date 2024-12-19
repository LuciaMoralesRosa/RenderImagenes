#include "escena.hpp"

void Escena::anadirPrimitiva(const shared_ptr<Primitiva> p){
    primitivas.push_back(p);
}

void Escena::anadirLuz(const shared_ptr<Luz> l){
    luces.push_back(l);
}

RGB Escena::sampledColor(const Direccion& dir) const {
    if(!textura) {
        return RGB();
    }

    double phi = atan2(dir.getZ(), -dir.getX()) + M_PI;
    double th = acos(dir.getY());

    return textura->sample(phi / (2 * M_PI), th / M_PI, Punto());
}



RGB Escena::colorDelRayo(const Rayo& r, Primitiva& p) const {
    Interseccion inter;
    inter = p.interseccion(r);
    if (inter.intersecta){
        return RGB(1 + inter.normal.getX(), 1 + inter.normal.getY(), 1 + inter.normal.getZ()) * 0.5;
    }

    Direccion unit_direction = normalizar(r.getDireccion());
    auto a = 0.5*(unit_direction.getY() + 1.0);
    return RGB(1.0, 1.0, 1.0) * (1.0 - a) + RGB(0.5, 0.7, 1.0) * a;
}
