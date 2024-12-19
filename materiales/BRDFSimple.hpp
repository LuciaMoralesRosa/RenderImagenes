#pragma once

#include <cmath>
#include <tuple>
#include <functional>
#include <random>

#include "../geometria/coordenadas.hpp"
#include "BRDF.hpp"
#include "../textura/textura.hpp"
#include "../geometria/Punto.hpp"
#include "../geometria/Direccion.hpp"
#include "../color/RGB.hpp"
#include "../varios/misc.hpp"



class BRDFSimple : public BRDF{
    private:
        enum TipoEvento {
            DIFUSO = 0,
            ESPECULAR,
            REFRACCION,
            ABSORCION
        };
        /**
         * @brief An enum for listing event types for the Russian roulette algorithm.
         * 
         * - Diffuse events scatter light in every direction.
         * - Reflection events only scatter light following the reflection law.
         * - Refraction events only scatter light following Snell's law:
         * 
         *  $ n_1 \cdot sin \theta_1 = n_2 \cdot sin \theta_2 $
         */


        /**
         * @brief Sample an outbound direction for a difuso surface
         * 
         * @param omega0 The inbound direction
         * @param x The intersection point
         * @param n The normal
         * @return Vector3 
         */
        Direccion sampleDifuso(const Direccion& omega0, const Punto& x, const Direccion& n) const;
        
        /**
         * @brief Sample an outbound direction for a reflective surface
         * 
         * @param omega0 The inbound direction
         * @param x The intersection point
         * @param n The normal
         * @return Vector3 
         */
        Direccion sampleEspecular(const Direccion& omega0, const Punto& x, const Direccion& n) const;
        
        /**
         * @brief Sample an outbound direction for a refractive surface
         * 
         * @param omega0 The inbound direction
         * @param x The intersection point
         * @param n The normal
         * @return Vector3 
         */
        Direccion sampleRefraccion(const Direccion& omega0, const Punto& x, const Direccion& n) const;
        
        /**
         * @brief Return the event type given a random value between 0 and 1.
         * 
         * @param t A value between 0 and 1
         * @return TipoEvento The event type
         */
        TipoEvento ruletaRusa(double t) const;

public:
    RGB difuso, especular, refraccion;
    double probDifuso, probEspecular, probRefraccion;

    double refractionIndex;

    /**
     * @brief Construct a new BRDF object and assign the probability 
     * for each event after a ray bounce automatically.
     * 
     * The probability for any given event will be given by the maximum value
     * of its colour channels.
     * 
     * @param d The difuso coefficient
     * @param s The especular coefficient
     * @param r The refractive coefficient
     * @param ri The refraccion index 
     */
    BRDFSimple(const RGB& d = RGB(), const RGB& s = RGB(), const RGB& r = RGB(), const double ri = 1) 
        : BRDF(false),
          difuso(d), 
          especular(s), 
          refraccion(r),
          probDifuso(canalMayor(difuso)), 
          probEspecular(canalMayor(especular)), 
          probRefraccion(canalMayor(refraccion)), 
          refractionIndex(ri) 
    {};

    /**
     * @brief Construct a new BRDF object and manually assign event probabilities
     * 
     * @param d The difuso coefficient
     * @param s The especular coefficient
     * @param r The refractive coefficient
     * @param pd The probability of a difuso event on a ray bounce
     * @param ps The probability of a especular event on a ray bounce
     * @param pr The probability of a refraccion event on a ray bounce
     * @param ri The refraccion index 
     */
    BRDFSimple(const RGB& d, const RGB& s, const RGB& r, 
         const double pd, const double ps, const double pr, const double ri) 
        : BRDF(false),
          difuso(d), 
          especular(s), 
          refraccion(r),
          probDifuso(pd), 
          probEspecular(ps), 
          probRefraccion(pr), 
          refractionIndex(ri) 
    {};

    /**
     * @brief Evaluate the BRDF on a point based on input and output directions
     * 
     * @param x The point in which the BRDF is evaluated
     * @param omegaI The input ray's direction
     * @param omega The output ray's direction
     * @param n The normal on the surface in which x lies
     * @return RGB The BRDF's result
     */
    RGB eval(const Punto& x, const Direccion& omegaI, const Direccion& omega, const Interseccion& it) const override;
    
    /**
     * @brief Sample the BRDF, return an outbound ray direction and the BRDF's value
     * 
     * @param omega0 The input ray's direction
     * @param x The point in which the BRDF is evaluated
     * @param n The normal on the surface in which x lies
     * @return tuple<Vector3, RGB> 
     */
    optional<BRDFInteraccion> sample(const Direccion& omega0, const Punto& x, const Interseccion& it) const override;
};