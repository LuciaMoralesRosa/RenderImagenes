#pragma once

#include "BRDF.hpp"
#include "../textura/textura.hpp"
#include "../geometria/Punto.hpp"
#include "../geometria/Direccion.hpp"
#include "../color/RGB.hpp"

#include <cmath>
#include <tuple>

class Emisor : public BRDF {
public:
    RGB emision;

    /**
     * @brief Construct a new Emisor object
     * 
     * @param e Emission value
     */
    Emisor(const RGB e = RGB()) : BRDF(true), emision(e) {};

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
     * @return tuple
     */
    optional<BRDFInteraccion> sample(const Direccion& omega0, const Punto& x, const Interseccion& it) const override;
};

class TexturaEmisor : public BRDF {
public:
    shared_ptr<Textura<RGB>> emision;

    /**
     * @brief Construct a new Emisor object
     * 
     * @param e Emission value
     */
    TexturaEmisor(const shared_ptr<Textura<RGB>>& e) : BRDF(true), emision(e) {};

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
     * @return tuple
     */
    optional<BRDFInteraccion> sample(const Direccion& omega0, const Punto& x, const Interseccion& it) const override;
};