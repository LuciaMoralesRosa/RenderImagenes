#include "Direccion.hpp"
#include <string>

double Direccion::modulo() const {
    return sqrt(this->getX() * this->getX() + this->getY() * this->getY() + this->getZ() * this->getZ());
}

Direccion Direccion::normalizada() const {
    return *this / modulo();
}

Direccion Direccion::proyeccion(const Direccion v) const {
    return v * (productoEscalar(v, *this) / productoEscalar(v, v));
}

Direccion Direccion::operator+(const Direccion& dir) const {
    return Direccion(this->getX() + dir.getX(), this->getY() + dir.getY(), this->getZ() + dir.getZ());
}

Direccion Direccion::operator-(const Direccion& dir) const {
    return Direccion(this->getX() - dir.getX(), this->getY() - dir.getY(), this->getZ() - dir.getZ());
}

Direccion Direccion::operator*(const double scalar) const {
    return Direccion(this->getX() * scalar, this->getY() * scalar, this->getZ() * scalar);
}

Direccion Direccion::operator/(const double scalar) const {
    return Direccion(this->getX() / scalar, this->getY() / scalar, this->getZ() / scalar);
}

Direccion Direccion::operator+(const double scalar) const {
    return Direccion(this->getX() + scalar, this->getY() + scalar, this->getZ() + scalar);
}

Direccion Direccion::operator-() const {
    return Direccion(-this->getX(), -this->getY(), -this->getZ());
}

const double Direccion::operator[](const unsigned int i) const {
    switch (i) {
    case 0:
        return this->getX();
        break;
    case 1:
        return this->getY();
        break;
    case 2:
        return this->getZ();
        break;
    default:
        throw runtime_error("La direccion solo tiene 3 componentes");
        break;
    }
}


bool Direccion::operator==(const Direccion& otro) const {
    return (this->getX() == otro.getX() && this->getY() == otro.getY() && this->getZ() == otro.getZ());
}

bool Direccion::operator!=(const Direccion& otro) const {
    return (this->getX() != otro.getX() && this->getY() != otro.getY() && this->getZ() != otro.getZ());
}

bool Direccion::operator>(const Direccion& otro) const {
    return (this->getX() > otro.getX() && this->getY() > otro.getY() && this->getZ() > otro.getZ());
}

bool Direccion::operator<(const Direccion& otro) const {
    return (this->getX() < otro.getX() && this->getY() < otro.getY() && this->getZ() < otro.getZ());
}

bool Direccion::operator>=(const Direccion& otro) const {
    return (this->getX() >= otro.getX() && this->getY() >= otro.getY() && this->getZ() >= otro.getZ());
}

bool Direccion::operator<=(const Direccion& otro) const {
    return (this->getX() <= otro.getX() && this->getY() <= otro.getY() && this->getZ() <= otro.getZ());
}

bool Direccion::esNula() const {
    return this->getX() == -1 && this->getY() == -1 && this->getZ() == -1;
}

// Print
ostream& operator<<(const Direccion& d, ostream& os) {
    os << "-->(" << d.getX() << ", " << d.getY() << ", " << d.getZ() << ")";
    return os;
}


double productoEscalar(Direccion u, Direccion v) {
    return u.getX() * v.getX() + u.getY() * v.getY() + u.getZ() * v.getZ();
}

Direccion productoVectorial(Direccion u, Direccion v) {
    return Direccion( u.getY()*v.getZ() - u.getZ()*v.getY(), u.getZ()*v.getX() - u.getX()*v.getZ(), u.getX()*v.getY() - u.getY()*v.getX());
}

Direccion perpendicular(Direccion d) {
    if ( (d.getZ() != 0) && (-d.getX() != d.getY()) ) {
        return Direccion(d.getZ(), d.getZ(), - d.getX() - d.getY());
    } else {
        return Direccion(d.getY() - d.getZ(), d.getX(), d.getX());
    }
}

bool mismaDireccionSentido(Direccion d, Direccion v) {
    return productoVectorial(d, v).modulo() < 0.0001 ? 1 : 0;
}

double angulo(Direccion d, Direccion v) {
    double pescalar = abs(productoEscalar(d, v));
    double modD = d.modulo();
    double modV = v.modulo();
    double c = pescalar / modD * modV;
    double ac = acos(c);

    return ac;
}

Direccion normalizar(const Direccion d) {
    return d.normalizada();
}

double obtenerModulo(const Direccion& v) {
    return v.modulo();
}

