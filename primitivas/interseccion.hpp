#pragma once

#include <iostream>

#include "../geometria/Direccion.hpp"
#include "../geometria/Punto.hpp"
#include "../materiales/BRDF.hpp"

using namespace std;

class BRDF;

/**
 * @brief Struct that carries general intersection info.
 * 
 */
struct Interseccion {

    bool intersecta;
    Punto punto;
    Direccion normal;
    double distancia;
    BRDF textura;
   
    friend ostream& operator<<(ostream& os, const Interseccion& it);
};

