#include "textura.hpp"

class ColorSolido : public Textura<RGB> {
    private:
        RGB color;

    public:
        ColorSolido(const RGB& r) : color(r) {}

        RGB sample(const double u, const double v, const Punto& p) const override {
            return color;
        }
};