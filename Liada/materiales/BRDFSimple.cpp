#include "BRDFSimple.hpp"


RGB BRDFSimple::eval(const Punto& x, const Direccion& omegaI, const Direccion& omega, const Interseccion& it) const {
    Direccion n = it.normal;
    Direccion specDir = sampleEspecular(omega, x, n);
    Direccion refDir = sampleRefraccion(omega, x, n);
    
    RGB dif = probDifuso > 0 ? difuso / probDifuso / M_PI : RGB();
    RGB spec = probEspecular > 0 ? especular * (mismaDireccionSentido(omegaI, specDir)) / probEspecular: RGB();
    RGB ref = probRefraccion > 0 ? refraccion * (mismaDireccionSentido(omegaI, refDir)) / probRefraccion: RGB();
    
    return dif + spec + ref;
}

Direccion BRDFSimple::sampleDifuso(const Direccion& omega0, const Punto& x, const Direccion& n) const {
    RandomGenerator rng(0, 1);
    
    double invTheta = acos(sqrt(1.0 - rng()));
    double invPhi = 2.0 * M_PI * rng();

    Direccion omega = Direccion(
        sin(invTheta) * cos(invPhi),
        sin(invTheta) * sin(invPhi),
        cos(invTheta)).normalizada();

    Direccion v1 = perpendicular(n);
    Direccion v2 = productoVectorial(v1, n);
    Direccion v3 = productoVectorial(v2, n);
    Coordenada local2Global(v2, v3, n, x, 1);
    Coordenada dir(Direccion(1,0,0), Direccion(0,1,0), Direccion(0,0,1), omega, 0);

    return Direccion(local2Global(dir).getPosition());
}

Direccion BRDFSimple::sampleEspecular(const Direccion& omega0, const Punto& x, const Direccion& n) const {
    return omega0 - n * 2 * productoEscalar(omega0, n);
}


Direccion BRDFSimple::sampleRefraccion(const Direccion& omega0, const Punto& x, const Direccion& n) const {

    double cosTh = min(productoEscalar(-omega0, n), 1.0);
    double sinTh = sqrt(1.0 - cosTh*cosTh);
    bool frontFace = productoEscalar(omega0, n) < 0; 

    Direccion ax = frontFace ? n : -n;

    // Assume objects are solid and don't clip
    double ratio = frontFace ? 1.0 / refractionIndex : refractionIndex;

    bool cannotRefract = ratio * sinTh > 1.0;
    if ( cannotRefract ) {
        return sampleEspecular(omega0, x, ax);
    } else {
        auto cos = min(productoEscalar(-omega0, ax), 1.0);

        // Compute refracted parallel and perpendicular component to normal
        Direccion rPerp = (omega0 + ax * cos) * ratio;
        Direccion rPar = -ax * sqrt(abs(1.0 - productoEscalar(rPerp, rPerp)));
        
        // Sum both components together
        return rPerp + rPar;
    }
}

BRDFSimple::TipoEvento BRDFSimple::ruletaRusa(double t) const {
    if (t < probDifuso) {
        return DIFUSO;
    } else if (t < probDifuso + probEspecular) {
        return ESPECULAR;
    } else if (t < probDifuso + probEspecular + probRefraccion) {
        return REFRACCION;
    } else {
        return ABSORCION;
    }
}

optional<BRDFInteraccion> BRDFSimple::sample(const Direccion& omega0, const Punto& x, const Interseccion& it) const{
    Direccion n = it.normal;
    
    RandomGenerator rng(0, 1);
    
    // Russian roulette
    double r = rng();
    Direccion dirSalida;
    RGB color;
    bool isDelta;
    switch (ruletaRusa(r)) {
    case DIFUSO:
        dirSalida = sampleDifuso(omega0, x, n);
        // * M_PI because of  uniform cos sampling
        color = eval(x, dirSalida, omega0, it) * M_PI;
        isDelta = false;
        break;
    case ESPECULAR:
        dirSalida = sampleEspecular(omega0, x, n);
        color = eval(x, dirSalida, omega0, it);
        isDelta = true;
        break;
    case REFRACCION:
        dirSalida = sampleRefraccion(omega0, x, n);
        color = eval(x, dirSalida, omega0, it);
        isDelta = true;
        break;
    default:
        return {};
    }

    return make_optional<BRDFInteraccion>(
        dirSalida,
        color,
        isDelta
    );
}