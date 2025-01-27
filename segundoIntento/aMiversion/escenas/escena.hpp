#pragma once

#include <list>

#include "../color/rgb.hpp"
#include "../escena/luz.hpp"
#include "../geometria/punto.hpp"
#include "../geometria/rayo.hpp"
#include "../geometria/direccion.hpp"
#include "../materiales/material.hpp"
#include "../materiales/brdf.hpp"
#include "../primitivas/primitiva.hpp"
#include "../primitivas/esfera.hpp"
#include "../primitivas/plano.hpp"
#include "../aleatorios/generadorAleatorios.hpp"
#include "../escena/camara.hpp"
#include "../imagen/imagenPPM.hpp"  


class Escena {
    protected:
    virtual void aniadirCamara(Camara& c) {}
    virtual void aniadirLuces(vector<Luz>& luces) {}
    virtual void aniadirPrimitivas(list<Primitiva*>& primitivas) {}
    
    public: 
    Escena() {};

    virtual void crearEscena(Camara& camara, list<Primitiva*>& primitivas, vector<Luz>& luces) = 0;

};