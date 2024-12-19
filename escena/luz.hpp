#pragma once

#include "../color/RGB.hpp"
#include "../geometria/Punto.hpp"
#include "../primitivas/rayo.hpp"
#include "../varios/misc.hpp"

class Luz {
    private:
        RGB potencia;
        int count = 0;
    public:
        Luz(RGB p) : potencia(p) {}
        virtual Rayo sample() const = 0;
        RGB getPotencia() { return potencia; }
};

class LuzPuntual : public Luz {
    private: 
    Punto centro;
    public:
    LuzPuntual(Punto p, RGB potencia) : centro(p), Luz(potencia) {}
    Rayo sample() const override;
    Punto getCentro() { return centro; }
};


class LuzArea : public Luz {
    public: 
    Rayo sample() const override;
};

