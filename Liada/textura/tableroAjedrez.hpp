#include <memory>

#include "textura.hpp"
#include "colorSolido.hpp"

class Checkerboard : public Textura<RGB> {
    private:
        shared_ptr<Textura> t1, t2;
        double xsize, ysize;

    public:
        Checkerboard(const RGB& c1, const RGB& c2, double x = 1, double y = 1) 
            : t1(make_shared<ColorSolido>(c1)),
            t2(make_shared<ColorSolido>(c2)),
            xsize(x),
            ysize(y)
            {}

        RGB sample(const double u, const double v, const Punto& p) const override {
            auto sines = sin(2 * M_PI * u / xsize)*sin(2 * M_PI * v / ysize);
            if (sines < 0)
                return t1->sample(u, v, p);
            else
                return t2->sample(u, v, p);
        }
};