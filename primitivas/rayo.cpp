#include "rayo.hpp"

Direccion corregirNormal(const Direccion& rdir, const Direccion& n){
    return productoEscalar(rdir, n) > 0 ? -n : n;
}
