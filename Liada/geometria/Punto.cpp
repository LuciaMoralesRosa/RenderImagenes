#include "Punto.hpp"

Punto::Punto(Punto origen, Direccion direccion, double distancia) {
    // Normalizar la direccion
    Direccion normalizada = direccion.normalizada();
    
    Punto p = origen + normalizada * distancia;
    vector = Vector3(p.getX(), p.getY(), p.getZ());
}

Direccion Punto::operator-(const Punto& otro) const {
    return Direccion(this->getX() - otro.getX(), this->getY() - otro.getY(), this->getZ() - otro.getZ());
}

Punto Punto::operator+(const Direccion& otro) const {
    return Punto(this->getX() - otro.getX(), this->getY() - otro.getY(), this->getZ() - otro.getZ());
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
    return this->getX() == -1 && this->getY() == -1 && this->getZ() == -1;
}
