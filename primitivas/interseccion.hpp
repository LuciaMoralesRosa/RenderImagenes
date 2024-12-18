#pragma once

#include <iostream>
#include <memory>  // Para usar std::shared_ptr

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
    shared_ptr<BRDF> textura;

    double u, v;
   
    friend ostream& operator<<(ostream& os, const Interseccion& it);
};

