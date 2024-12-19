#include "emisor.hpp"

RGB Emisor::eval(const Punto& x, const Direccion& omegaI, const Direccion& omega, const Interseccion& it) const {
    return emision;
}

optional<BRDFInteraccion> Emisor::sample(const Direccion& omega0, const Punto& x, const Interseccion& it) const {
    return make_optional<BRDFInteraccion>(Vector3(), emision, false);
}

RGB TexturaEmisor::eval(const Punto& x, const Direccion& omegaI, const Direccion& omega, const Interseccion& it) const {
    return emision->sample(it.u, it.v, x);
}

optional<BRDFInteraccion> TexturaEmisor::sample(const Direccion& omega0, const Punto& x, const Interseccion& it) const {
    return make_optional<BRDFInteraccion>(Vector3(), emision->sample(it.u, it.v, x), false);
}