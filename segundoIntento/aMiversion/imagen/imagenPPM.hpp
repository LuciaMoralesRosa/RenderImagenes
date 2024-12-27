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
    ImagenPPM(int base, int altura, float valorMax, string comentario = "") :
        base(base), altura(altura), valorMax(valorMax), comentario(comentario),
        resolucion(0), arrayPixeles() {}

    void establecerPixeles(vector<RGB> pixeles) { arrayPixeles = pixeles; }
    void escribirImagen(string fichero) {
        // Apertura del fichero donde escribir la imagen
        ofstream salida(fichero);
        if (!salida.is_open()) {
            // Si no se puede abrir el fichero
            cerr << "Error en la apertura del fichero \"" << fichero << "\"" << endl;
            exit(1);
        }

                // Escribir la cabecera de la imagen
        salida << "P3" << endl;
        salida << base << " " << altura << endl;

        // Escribir el valor maximo de los pixeles
        salida << valorMax << endl;

        // Escribir los pixeles en la imagen
        for (int i = 0; i < altura; i++) {
            for (int j = 0; j < base; j++) {
                RGB color = arrayPixeles[j * altura + i];
                salida << color << "    ";
            }
            salida << endl;
        }
        salida.close();
    }
};