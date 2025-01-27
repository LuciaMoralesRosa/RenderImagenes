#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "../color/rgb.hpp"

using namespace std;

class ImagenPPM {
    private:
    int base, altura;

    string formato = "P3";
    float valorMax;
    string comentario;
    float resolucion;

    vector<RGB> arrayPixeles;

    public:
    ImagenPPM() : formato(""), valorMax(0), comentario(""), base(0), altura(0),
        resolucion(0), arrayPixeles() {}

    ImagenPPM(int base, int altura, float valorMax, vector<RGB> pixeles,
        string comentario = "") : base(base), altura(altura), valorMax(valorMax),
        comentario(comentario), resolucion(0) {arrayPixeles = pixeles;}

    void escribirImagen(string fichero) {
        // Apertura del fichero donde escribir la imagen
        ofstream output(fichero);
        if (!output.is_open()) {
            cerr << "Error abriendo el fichero de salida \"" << fichero << "\"" << endl;
            exit(1);
        }

        // Write the header of the PPM file.
        output << "P3" << endl;
        output << base << " " << altura << endl;

        output << valorMax << endl;

        for (int i = 0; i < altura; i++) {
            for (int j = 0; j < base; j++) {
                output << arrayPixeles[i*base + j] << " ";
            }
            output << endl;
        }
        output.close();
    }
};