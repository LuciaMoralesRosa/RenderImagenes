#pragma once

#include <tuple>
#include <functional>
#include <optional>

#include "../geometria/vector.hpp"
#include "../geometria/Direccion.hpp"
#include "../geometria/Punto.hpp"
#include "../color/RGB.hpp"
#include "../primitivas/interseccion.hpp"

// Forward declaration of Intersection because of circular includes.
struct Interseccion;

struct BRDFInteraccion {
    Direccion outDirection;
    RGB radiance;
    bool isDelta;

    BRDFInteraccion(const Direccion& o, const RGB& r, bool delta) 
    : outDirection(o), radiance(r), isDelta(delta) {}
};

class BRDF {
    private:
        bool emisor;
    public:
        BRDF(bool emite) : emisor(emite) {}

        /**
         * @brief Evaluate the BRDF on a point based on input and output directions
         * 
         * @param x The point in which the BRDF is evaluated
         * @param omegaI The input ray's direction
         * @param omega The output ray's direction
         * @param n The normal on the surface in which x lies
         * @return RGB The BRDF's result
         */
        virtual RGB eval(const Punto& x, const Direccion& omegaI, 
            const Direccion& omega, const Interseccion& it) const = 0;

        /**
         * @brief Sample the BRDF, return an outbound ray direction and the BRDF's value
         * 
         * @param omega0 The input ray's direction
         * @param x The point in which the BRDF is evaluated
         * @param n The normal on the surface in which x lies
         * @return tuple<Vector3, RGB> 
         */
        virtual optional<BRDFInteraccion> sample(const Direccion& omega0, 
            const Punto& x, const Interseccion& it) const = 0;

        // Getters
        bool esEmisor() { return emisor; }
};