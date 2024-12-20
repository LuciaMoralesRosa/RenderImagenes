#pragma once

#include <functional>
#include <memory>
#include <cmath>
#include <random>
#include <iomanip>

#include "../color/RGB.hpp"
#include "../imagen/imagenPPM.hpp"
#include "../geometria/Direccion.hpp"
#include "../geometria/Punto.hpp"
#include "../geometria/coordenadas.hpp"
#include "../primitivas/rayo.hpp"
#include "../primitivas/primitiva.hpp"
#include "../textura/textura.hpp"
#include "camara.hpp"
#include "luz.hpp"

using namespace std;

struct ValoresEscena{
    uint32_t width, height;
    uint32_t factorAntialising;
    uint32_t hilos;

    unsigned int rebotes = 5;
};

class Escena {
    private:
        ValoresEscena valores;
        shared_ptr<Textura<RGB>> textura;
        Camara camara;

    public:
        vector<shared_ptr<Primitiva>> primitivas;
        vector<shared_ptr<Luz>> luces;
        using RenderMethod = function<ImagenPPM(const Escena&)>;

        Escena(ValoresEscena v, Camara c, const shared_ptr<Textura<RGB>> tex = nullptr) : camara(c), valores(v), textura(tex) {};
        
        void anadirPrimitiva(const shared_ptr<Primitiva> p);
        void anadirLuz(const shared_ptr<Luz> l);

        ImagenPPM dibujarEscena(const RenderMethod& method) { return method(*this); }
        RGB sampledColor(const Direccion& dir) const;
        RGB colorDelRayo(const Rayo& r, Primitiva& p) const;

        //Getters
        ValoresEscena getValores() const { return valores; }
        Camara getCamara() const { return camara; }

};