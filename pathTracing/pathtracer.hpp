#pragma once

#include <cmath>
#include <functional>
#include <random>
#include <iomanip>

#include "../imagen/imagenPPM.hpp"
#include "../escena/escena.hpp"
#include "../materiales/BRDF.hpp"
#include "../varios/threadPool.hpp"

using namespace std;

struct Pixel {
    unsigned int x, y;
    RGB contribucion;
};

/**
 * @brief Estimate direct light contribution on a point given the observation
 * direction and intersection data.
 * 
 * @param sc The scene
 * @param origin The point of intersection
 * @param it The intersection data
 * @return RGB The direct light contribution
 */
RGB nextEventEstimation(const Escena& sc, const Punto origin, const Interseccion& it);

/**
 * @brief Render the scene onto an image with the path tracing algorithm.
 * 
 * @param sc The scene
 * @return Image The rendered image
 */
ImagenPPM pathTracing(const Escena& sc);