#include "RGB.hpp"


double RGB::getLuminancia() const {
    return 0.299 * r +0.587 * g + 0.114 * b;
}

string RGB::toString() const {
    ostringstream ss;
    ss << "R: " << r << ", G: " << g << ", B: " << b;
    return ss.str();
}

ostream& operator<<(ostream& os, const RGB& color) {
    os << "RGB(" << color.toString() << ")";
    return os;
}


RGB clamp(const RGB& color, double v) {
    double r = v > color.getR() ? color.getR() : v;
    double g = v > color.getG() ? color.getG() : v;
    double b = v > color.getB() ? color.getB() : v;
    return RGB(r, g, b);
}

RGB equalize(const RGB& color, double v) {
    return RGB(color.getR() / v, color.getG() / v, color.getB() / v);
}

RGB equalizeClamp(const RGB& color, double v) {
    double r = color.getR() > v ? 1.0 : color.getR() / v; 
    double g = color.getG() > v ? 1.0 : color.getG() / v; 
    double b = color.getB() > v ? 1.0 : color.getB() / v; 
    return RGB(r, g, b);
}

RGB gammaCorrection(const RGB& color, double k, double gamma){
    double r = color.getR() > k ? k : (pow(color.getR(), gamma) / pow(k, gamma));
    double g = color.getG() > k ? k : (pow(color.getG(), gamma) / pow(k, gamma));
    double b = color.getB() > k ? k : (pow(color.getB(), gamma) / pow(k, gamma));
    return RGB(r, g, b);
}

RGB gammaClamp(const RGB& color, double k, double gamma) {
    return clamp(gammaCorrection(color, k, gamma), 1);
}

RGB extendedReinhard(const RGB& color, double blancoMax) {
    RGB num = color * ( color / (blancoMax * blancoMax) + 1 );
    RGB den = color + 1;
    return num / den;
}

RGB unchartedParcial(const RGB& x) {
    double A = 0.15f;
    double B = 0.50f;
    double C = 0.10f;
    double D = 0.20f;
    double E = 0.02f;
    double F = 0.30f;
    return ((x * (x*A + C*B) + D*E) / (x * (x*A + B) + D*F)) - E/F;
}

RGB filmicUncharted(const RGB& v)
{
    double exposicion = 2.0;
    RGB curr = unchartedParcial(v * exposicion);

    RGB W = RGB(11.2, 11.2, 11.2);
    RGB escalaBlanco = RGB(1.0, 1.0, 1.0) / unchartedParcial(W);
    return clamp(curr * escalaBlanco, 1);
}

