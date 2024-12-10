#pragma once 

#include <iostream>

#include "imagen.hpp"

using namespace std;

namespace tonemapping {

    /* Global tone mapping operators */

    Imagen clamp(const Imagen& Imagen);

    Imagen equalize(const Imagen& Imagen);

    Imagen gamma(const Imagen& Imagen, double gamma);

    Imagen equalizeClamp(const Imagen& Imagen, double v);

    Imagen gammaClamp(const Imagen& Imagen, double gamma);

    Imagen simpleReinhard(const Imagen& Imagen, const double a, const double delta);

    Imagen extendedReinhard(const Imagen& Imagen, const double a, const double delta, const double lwhite);

    Imagen filmicUncharted(const Imagen& Imagen);

    /* Local tone mapping operators */
/*
    Imagen localReinhard(const Imagen& Imagen,
        double key, double sharp, double center, double surround, double threshold);
*/
}