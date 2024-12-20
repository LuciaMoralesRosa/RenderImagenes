#pragma once

#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

class RGB {
    private:
    double r, g, b;

    public:
    // Constructores
    inline RGB() : r(0), g(0), b(0) {}
    inline RGB(double red, double green, double blue) : r(red), g(green), b(blue) {}

    double getLuminancia() const;
    bool esNulo() { return (r == -1 && g == -1 && b == -1); }
    bool esNegro() { return (r == 0 && g == 0 && b == 0); }
    
    // Setters y getters
    double getR() const { return r; }   
    double getG() const { return g; }
    double getB() const { return b; }
    void setR(const double valor) { r = valor; }
    void setG(const double valor) { g = valor; }
    void setB(const double valor) { b = valor; }

    // Operadores
    inline RGB operator+(const RGB& otro) const { return RGB(r + otro.r, g + otro.g, b + otro.b); }
    inline RGB operator-(const RGB& otro) const { return RGB(r - otro.r, g - otro.g, b - otro.b); }
    inline RGB operator*(const RGB& otro) const { return RGB(r * otro.r, g * otro.g, b * otro.b); }
    inline RGB operator/(const RGB& otro) const { return RGB(r / otro.r, g / otro.g, b / otro.b); }
    inline RGB operator+(double f) const { return RGB(r + f, g + f, b + f); }
    inline RGB operator-(double f) const { return RGB(r - f, g - f, b - f); }
    inline RGB operator*(double f) const { return RGB(r * f, g * f, b * f); }
    inline RGB operator/(double f) const { return RGB(r / f, g / f, b / f); }

    friend ostream& operator<<(ostream& os, const RGB& color);
    
    // To string
    string toString() const;
};

inline double canalMayor(const RGB& color) { return max(color.getR(), max(color.getG(), color.getB())); }
inline RGB cambiarLuminancia(const RGB& color, double nuevaLuminancia) { return color * ( nuevaLuminancia / color.getLuminancia() ); }

RGB clamp(const RGB& color, double v);
RGB equalize(const RGB& color, double v);
RGB equalizeClamp(const RGB& color, double v);
RGB gammaCorrection(const RGB& color, double k, double gamma);
RGB gammaClamp(const RGB& color, double k, double gamma);
RGB extendedReinhard(const RGB& col, double maxWhite);
RGB filmicUncharted(const RGB& v);