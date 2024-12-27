#include "rgb.hpp"

//------------------------------- CONSTRUCTORES ------------------------------//
RGB::RGB() : RGB(0) {}

RGB::RGB(double red, double green, double blue) : r(red), g(green), b(blue) {}

RGB::RGB(double w) : RGB(w, w, w) {}
//------------------------------- CONSTRUCTORES ------------------------------//


//----------------------------- METODOS PRIVADOS -----------------------------//
//----------------------------- METODOS PRIVADOS -----------------------------//


//----------------------------- METODOS PUBLICOS -----------------------------//
double RGB::maxC() const {
    if(r > g) {
        return r > b ? r : b;
    }
    else {
        return g > b ? g : b;
    }
}

double RGB::maxC(char& canal) const {
    double valor; 
    if(r > g){
        if(r > b){
            valor = r;
            canal = R;
        } else {
            valor = b;
            canal = B;
        }
    } else {
        if(g > b){
            valor = g;
            canal = G;
        } else {
            valor = b;
            canal = B;
        }
    }
    return valor;
}

double RGB::sumarComponentes(){
    return r + g + b;
}

bool RGB::esNulo() const {
    return r == -1 && g == -1 && b == -1;
}

bool RGB::esNegro() const {
    return r == 0 && g == 0 && b == 0;
}

bool RGB::esBlanco() const {
    return r == 1 && g == 1 && b == 1;
}
//----------------------------- METODOS PUBLICOS -----------------------------//


//-------------------------------- OPERADORES --------------------------------//
RGB operator+(const RGB& c1, const RGB& c2) {
    return RGB(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

RGB operator+=(RGB& c1, const RGB& c2) {
    c1 = c1 + c2;
    return c1;
}

RGB operator-(const RGB& c1, const RGB& c2) {
    return RGB(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
}

RGB operator-=(RGB& c1, const RGB& c2) {
    c1 = c1 - c2;
    return c1;
}

RGB operator*(const RGB& c, double k) {
    return RGB(c.r * k, c.g * k, c.b * k);
}

RGB operator*=(RGB& c, double k) {
    c = c * k;
    return c;
}

RGB operator*(double k, const RGB& c) {
    return RGB(c.r * k, c.g * k, c.b * k);  
}

RGB operator*(const RGB& c1, const RGB& c2) {
    return RGB(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
}

RGB operator*=(RGB& c1, const RGB& c2) {
    c1 = c1 * c2;
    return c1;
}

RGB operator/(const RGB& c, double k) {
    return RGB(c.r / k, c.g / k, c.b / k);
}

RGB operator/=(RGB& c, double k) {
    c = c / k;
    return c;
}

bool operator==(RGB c1, RGB c2) {
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
}


bool operator!=(RGB c1, RGB c2) {
    return !(c1 == c2);
}

const double& RGB::operator[](int i) const {
    switch(i) {
			case R:
				return r;
			case G:
				return g;
			case B:
				return b;
			default:
				throw invalid_argument("Indice invalido");
		}
}

ostream &operator<< (ostream &o, const RGB &c){
    o << c[0] << " " << c[1] << " " << c[2];
    return o;
}

istream &operator>> (istream &i, RGB &c){
    i >> c.c[0] >> c.c[1] >> c.c[2];
    return i;
}
//-------------------------------- OPERADORES --------------------------------//
