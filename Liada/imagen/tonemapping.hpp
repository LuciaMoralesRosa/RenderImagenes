#pragma once

#include <iostream>
#include "imagenPPM.hpp"

using namespace std;

namespace tonemapping {

    ImagenPPM clamp(const ImagenPPM& imagen, const int valor = 1);
    ImagenPPM equalize(const ImagenPPM& imagen);
    ImagenPPM gamma(const ImagenPPM& imagen, double gamma);
    ImagenPPM equalizeClamp(const ImagenPPM& imagen, double v);
    ImagenPPM gammaClamp(const ImagenPPM& imagen, double gamma);

    ImagenPPM simpleReinhard(const ImagenPPM& imagen, const double a, const double delta);
    ImagenPPM extendedReinhard(const ImagenPPM& imagen, const double a, const double delta, const double lwhite);
    ImagenPPM filmicUncharted(const ImagenPPM& imagen);
}