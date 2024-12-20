#pragma once

#include <memory>
#include <tuple>

#include "../geometria/vector.hpp"
#include "../geometria/Direccion.hpp"
#include "../geometria/Punto.hpp"
#include "primitiva.hpp"
#include "interseccion.hpp"
#include "rayo.hpp"


using namespace std;

/**
 * @brief XZ plane-aligned rectangle.
 * 
 */
class RectanguloXZ : public Primitiva {
    private:
        double x0, x1, z0, z1, k;
        tuple<double, double> getUVCoords(const Punto& p);

    public:
        RectanguloXZ(double l, double r, double b, double t, double _k, const shared_ptr<BRDF>& brdf)
            : Primitiva(brdf), x0(l), x1(r), z0(b), z1(t), k(_k) {}

        RectanguloXZ(double w, double h, const Punto& o, const shared_ptr<BRDF>& brdf);

        Interseccion interseccion(const Rayo& r, double minT, double maxT) override;
};

/**
 * @brief XY plane-aligned rectangle.
 * 
 */
class RectanguloXY : public Primitiva {
    private:
        double x0, x1, y0, y1, k;
        tuple<double, double> getUVCoords(const Punto& p);

    public:
        RectanguloXY(double l, double r, double b, double t, double _k, const shared_ptr<BRDF>& brdf)
            : Primitiva(brdf), x0(l), x1(r), y0(b), y1(t), k(_k) {}

        RectanguloXY(double w, double h, const Punto& o, const shared_ptr<BRDF>& brdf);

        Interseccion interseccion(const Rayo& r, double minT, double maxT) override;
};

/**
 * @brief YZ plane-aligned rectangle.
 * 
 */
class RectanguloYZ : public Primitiva {
    private:
        double y0, y1, z0, z1, k;
        tuple<double, double> getUVCoords(const Punto& p);

    public:
        RectanguloYZ(double l, double r, double b, double t, double _k, const shared_ptr<BRDF>& brdf)
            : Primitiva(brdf), y0(l), y1(r), z0(b), z1(t), k(_k) {}
        RectanguloYZ(double w, double h, const Punto& o, const shared_ptr<BRDF>& brdf);

        Interseccion interseccion(const Rayo& r, double minT, double maxT) override;
};