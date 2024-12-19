#pragma once

#include <list>
#include <random>

#include "../color/RGB.hpp"
#include "../geometria/Direccion.hpp"
#include "../geometria/Punto.hpp"
#include "../geometria/coordenadas.hpp"
#include "../primitivas/rayo.hpp"
#include "../primitivas/primitiva.hpp"


using namespace std;

class Camara {
    private:
    Direccion u, l, f;
    Punto origen;
    int tamPlanoImagen[2]; //width, height

    public:
    Camara(Direccion u, Direccion l, Direccion f, Punto o, int w = 256, int h = 256)
        : l(l), u(u), f(f) { tamPlanoImagen [0] = w; tamPlanoImagen[1] = h; }

    list<Rayo> rayoPorPixel(unsigned int x, unsigned int y, unsigned int nRayos) const;
    

};