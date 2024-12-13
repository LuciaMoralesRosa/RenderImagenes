
/*
mult por escalar
resta de puntos (dir)
distancia entre dos puntos
trasladar
*/
#pragma once

#define M_PI           3.14159265358979323846  /* pi */

#include <iostream>
#include <math.h>
#include "vector.hpp"
using namespace std;

class Direccion {
    private:
    Vector3 vector;
    
    public:
    Direccion(double x = 0, double y = 0, double z = 0) : vector(x, y, z) {}


    double modulo() const;
    Direccion normalizada() const;

    /**
     * @brief Devuelve la proyeccion de la direccion sobre v
     */
    Direccion proyeccion(const Direccion v) const;

    //Operadores
    Direccion operator+(const Direccion& dir) const;
    Direccion operator-(const Direccion& dir) const;
    Direccion operator*(const double scalar) const;
    Direccion operator/(const double scalar) const;
    Direccion operator+(const double scalar) const;
    Direccion operator-() const;
    const double& operator[](const unsigned int i) const;


    // Comparadores
    bool operator==(const Direccion& otro) const;    
    bool operator!=(const Direccion& otro) const;
    bool operator>(const Direccion& otro) const;
    bool operator<(const Direccion& otro) const;
    bool operator>=(const Direccion& otro) const;
    bool operator<=(const Direccion& otro) const;
    bool esNula() const;

    // Getters y setters
    double getX() const {return vector.x; }
    double getY() const {return vector.y; }
    double getZ() const {return vector.z; }

    void setX(const double valor) {vector.x = valor; }
    void setY(const double valor) {vector.y = valor; }
    void setZ(const double valor) {vector.z = valor; }

    friend ostream& operator<<(const Direccion& d, ostream& os);

};

double productoEscalar(const Direccion u, const Direccion v);
Direccion productoVectorial(const Direccion u, const Direccion v);
Direccion normalizada(const Direccion d) { return d.normalizada(); }
Direccion perpendicular(const Direccion d);
bool mismaDireccionSentido(Direccion d, Direccion v);
double angulo(Direccion d, Direccion v);
double modulo(const Direccion& v) { return v.modulo(); }
