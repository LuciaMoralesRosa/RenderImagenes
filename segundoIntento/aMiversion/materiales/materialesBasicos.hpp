#include "material.hpp"

class Espejo : public Material {
    public:
    Espejo() : Material(RGB(0), RGB(1), RGB(0), RGB(0), 1) {}
};

class Hielo : public Material {
    public:
    Hielo() : Material(RGB(0.1), RGB(0.2), RGB(0.6), RGB(0), 1.31) {}
};

class Agua : public Material {
    public:
    Agua() : Material(RGB(0), RGB(0.1), RGB(0.9, 0.9, 1), RGB(0), 1.33) {}
};

class Oro : public Material {
    public:
    Oro() : Material(RGB(0.3, 0.2, 0), RGB(0.7, 0.5, 0.1), RGB(0), RGB(0), 1) {}
};

class Difuso : public Material {
    public:
    Difuso(const RGB& color) : Material(color, RGB(0), RGB(0), RGB(0), 1) {}
};

class Especular : public Material {
    public:
    Especular(const RGB& color) : Material(RGB(0), color, RGB(0), RGB(0), 1) {}
};

class Translucido : public Material {
    public:
    Translucido(const RGB& color) : Material(RGB(0), RGB(0.1), color, RGB(0), 1.5) {}
};

class Plastico : public Material {
    public:
    Plastico(const RGB& color) : Material(color, RGB(0.3), RGB(0.1), RGB(0), 1.3) {}
};