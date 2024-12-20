#pragma once

#include <fstream>
#include <iostream>
#include <vector>

#include "../color/RGB.hpp"

using namespace std;

class ImagenPPM {
    private:
    unsigned int base, altura;
    double valorMax;
    vector<vector<RGB>> matrizPixeles;

    public:
    // Constructores
    ImagenPPM(unsigned int w, unsigned int h) : base(w), altura(h), valorMax(1), matrizPixeles(h, vector<RGB>(w)) {}
    ImagenPPM(unsigned int w, unsigned int h, vector<vector<RGB>> pixeles, double max) : base(w), altura(h), valorMax(max), matrizPixeles(pixeles) {}
    ImagenPPM(const string& fichero);

    // Metodos
    void escrituraPPM(const string& path, unsigned int res = 255) const;
    static ImagenPPM lecturaPPM(const string& fichero);

    // Getters y setters
    double getNumeroMayor() const;
    unsigned int getBase() const { return base; }
    unsigned int getAltura() const { return altura; }
    double getValorMax() const { return valorMax; }
    vector<vector<RGB>> getMatrizPixeles() const { return matrizPixeles; }

    void setBase(const unsigned int b) { base = b; }
    void setAltura(const unsigned int a) { altura = a; }
    void setValorMax(const double max) { valorMax = max; }
    void setMatrizPixeles(const vector<vector<RGB>> matriz) { matrizPixeles = matriz; }
    void setPixelMatriz(const int fil, const int col, const RGB color) {matrizPixeles[fil][col] = color; }

    // Operadores
    friend ostream& operator<<(ostream& os, const ImagenPPM& imagen);

};