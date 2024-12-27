#include "vector.hpp"

//------------------------------- CONSTRUCTORES ------------------------------//
Vector::Vector() : x(0), y(0), z(0), esPunto(0) {}

Vector::Vector(float x, float y, float z, uint8_t esPunto) : x(x), y(y), z(z),
    esPunto(esPunto) {}
//------------------------------- CONSTRUCTORES ------------------------------//


//----------------------------- METODOS PRIVADOS -----------------------------//
void Vector::aplicarMatriz(Matriz m) {
    Vector aux = Vector(0, 0, 0, 0);

    aux.x = m.obtenerComponente(0, 0) * x + m.obtenerComponente(0, 1) * y +
        m.obtenerComponente(0, 2) * z + m.obtenerComponente(0, 3) * esPunto;
    aux.y = m.obtenerComponente(1, 0) * x + m.obtenerComponente(1, 1) * y +
    m.obtenerComponente(1, 2) * z + m.obtenerComponente(1, 3) * esPunto;
    aux.z = m.obtenerComponente(2, 0) * x + m.obtenerComponente(2, 1) * y +
    m.obtenerComponente(2, 2) * z + m.obtenerComponente(2, 3) * esPunto;

    aux.esPunto = m.obtenerComponente(3, 0) * x + m.obtenerComponente(3, 1) *
        y + m.obtenerComponente(3, 2) * z + m.obtenerComponente(3, 3) * esPunto;

    *this = aux;
}
//----------------------------- METODOS PRIVADOS -----------------------------//


//----------------------------- METODOS PUBLICOS -----------------------------//
float Vector::modulo() const {
    return sqrt(x * x + y * y + z * z);
}

Vector Vector::normalizar() const {
    return *this / modulo();
}

float escalar(const Vector &c1, const Vector &c2) {
    return c1.x * c2.x + c1.y * c2.y + c1.z * c2.z;
}

Vector vectorial(const Vector &c1, const Vector &c2) {
    return Vector(c1.y * c2.z - c1.z * c2.y, 
                    c1.z * c2.x - c1.x * c2.z, 
                    c1.x * c2.y - c1.y * c2.x, 
                    0);
}

void Vector::trasladar(double x, double y, double z) {
    Matriz m = Matriz();
    m.matrizTraslacion(x, y, z);
    this->aplicarMatriz(m);
}

void Vector::escalar(double x, double y, double ) {
    Matriz m = Matriz();
    m.matrizEscala(x, y, z);
    this->aplicarMatriz(m);
}

void Vector::rotarX(double degrees) {
    Matriz m = Matriz();
    m.matrizRotacionX(degrees);
    this->aplicarMatriz(m);
}

void Vector::rotarY(double degrees) {
    Matriz m = Matriz();
    m.matrizRotacionY(degrees);
    this->aplicarMatriz(m);
}

void Vector::rotarZ(double degrees) {
    Matriz m = Matriz();
    m.matrizRotacionZ(degrees);
    this->aplicarMatriz(m);
}

void Vector::cambiarBase(Vector o, Vector u, Vector v, Vector w) {
    Matriz m = Matriz();
    m.establecerComponente(0, 0, u.x);
    m.establecerComponente(1, 0, u.y);
    m.establecerComponente(2, 0, u.z);
    m.establecerComponente(0, 1, v.x);
    m.establecerComponente(1, 1, v.y);
    m.establecerComponente(2, 1, v.z);
    m.establecerComponente(0, 2, w.x);
    m.establecerComponente(1, 2, w.y);
    m.establecerComponente(2, 2, w.z);
    m.establecerComponente(0, 3, o.x);
    m.establecerComponente(1, 3, o.y);
    m.establecerComponente(2, 3, o.z);
    m.establecerComponente(3, 3, 1);
    
    this->aplicarMatriz(m);
}

void Vector::cambiarBaseInvertida(Vector o, Vector u, Vector v, Vector w) {
    Matriz m = Matriz();
    m.establecerComponente(0, 0, u.x);
    m.establecerComponente(1, 0, u.y);
    m.establecerComponente(2, 0, u.z);
    m.establecerComponente(0, 1, v.x);
    m.establecerComponente(1, 1, v.y);
    m.establecerComponente(2, 1, v.z);
    m.establecerComponente(0, 2, w.x);
    m.establecerComponente(1, 2, w.y);
    m.establecerComponente(2, 2, w.z);
    m.establecerComponente(0, 3, o.x);
    m.establecerComponente(1, 3, o.y);
    m.establecerComponente(2, 3, o.z);
    m.establecerComponente(3, 3, 1);
    m.invertirMatriz();

    this->aplicarMatriz(m);
}

array<float, 3> Vector::convertirArray() const {
    return {x, y, z};
}

double anguloEntreDirecciones(const Vector &c1, const Vector &c2) {
    return acos(escalar(c1, c2) /(c1.modulo() * c2.modulo()));
}

Vector distancia(Vector p1, Vector p2) {
    return Vector(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z, 0);
}
//----------------------------- METODOS PUBLICOS -----------------------------//


//-------------------------------- OPERADORES --------------------------------//
Vector operator+(const Vector &c1, const Vector &c2) {
    return Vector(c1.x + c2.x, c1.y + c2.y, c1.z + c2.z, c1.esPunto);
}

Vector operator-(const Vector &c1, const Vector &c2) {
    return Vector(c1.x - c2.x, c1.y - c2.y, c1.z - c2.z, c1.esPunto);
}

Vector operator-(const Vector &c) {
    return Vector(-c.x, -c.y, -c.z, c.esPunto);
}

Vector operator*(const Vector &c, const double &s) {
    return Vector(c.x * s, c.y * s, c.z * s, 0);
}

Vector operator*(const double &s, const Vector &c) {
    return c * s;
}

Vector operator/(const Vector &c, const double &s) {
    return Vector(c.x / s, c.y / s, c.z / s, 0);
}

Vector operator/(const double &s, const Vector &c) {
    return c / s;
}

bool operator==(const Vector &c1, const Vector &c2) {
    return c1.x == c2.x && c1.y == c2.y && c1.z == c2.z && c1.esPunto == c2.esPunto;
}

const float& Vector::operator[](int i) const {
    switch(i%3) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }
    return x;
}

ostream &operator<<(ostream &o, const Vector &c){
    o <<(c.esPunto?"(":"[") << c.x << ", " << c.y << ", " << c.z <<(c.esPunto?")":"]");
    return o;
}
//-------------------------------- OPERADORES --------------------------------//
