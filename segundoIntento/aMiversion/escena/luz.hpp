#pragma once

#include "../color/rgb.hpp"
#include "../geometria/punto.hpp"

class Luz {
    public:
    Punto centro;
    RGB potencia;

    Luz(const Punto& centro, const RGB& potencia) : centro(centro),
        potencia(potencia) {}
};