#pragma once

#define M_PI           3.14159265358979323846  /* pi */

#include <iostream>
#include <math.h>
#include "Direccion.hpp"
#include "vector.hpp"

using namespace std;

class Punto {
    private:
    Vector3 vector;
    
    public:
    Punto(double x = 0, double y = 0, double z = 0) : vector(x, y, z) {}
    Punto(Punto origen, Direccion direccion, double distancia);

    Direccion operator-(Punto& otro) const;
    Punto operator*(const double scalar) const;
    Punto operator/(const double scalar) const;

    bool operator==(Punto& otro) const;    
    bool operator!=(Punto& otro) const;

    bool esNulo() const;

    // Getters y setters
    double getX() const {return vector.x; }
    double getY() const {return vector.y; }
    double getZ() const {return vector.z; }

    void setX(const double valor) {vector.x = valor; }
    void setY(const double valor) {vector.y = valor; }
    void setZ(const double valor) {vector.z = valor; }

    friend ostream& operator<<(Punto& d, ostream& os);
};
