#include "Punto.hpp"

// Punto::Punto(Punto origen, Direccion direccion, double distancia) {
//     // Normalizar la direccion
//     Direccion normalizada = direccion.normalizada();
//     //TODO
// }

Direccion Punto::operator-(Punto& otro) const {
    return Direccion(this->getX() - otro.getX(), this->getY() - otro.getY(), this->getZ() - otro.getZ());
}

Punto Punto::operator*(const double scalar) const {
    return Punto(this->getX() * scalar, this->getY() * scalar, this->getZ() * scalar);
}

Punto Punto::operator/(const double scalar) const {
    return Punto(this->getX() / scalar, this->getY() / scalar, this->getZ() / scalar);
}

bool Punto::operator==(Punto& otro) const {
    return (this->getX() == otro.getX() && this->getY() == otro.getY() && this->getZ() == otro.getZ());
}

bool Punto::operator!=(Punto& otro) const {
    return (this->getX() != otro.getX() || this->getY() != otro.getY() || this->getZ() != otro.getZ());
}

bool Punto::esNulo() const {
    return *this == Punto(-1, -1, -1);
}
