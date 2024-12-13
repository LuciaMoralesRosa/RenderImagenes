#include <iostream>
#include <string>


#include "../color/RGB.hpp"
// #include "../geometria/Direccion.hpp"
// #include "../geometria/Punto.hpp"
#include "../imagen/imagenPPM.hpp"
#include "../imagen/tonemapping.hpp"

/* Compilacion:
g++ testing.cpp ../color/RGB.cpp ../imagen/imagenPPM.cpp ../imagen/tonemapping.cpp -o testing

*/



void test_ImagenTonemappingColor() {
    cout << "Inicio del test: test_ImagenTonemappingColor ---------------------" << endl;

    string imagenPrueba = "../testsImagenes/test_ImagenesEjemplo/forest_path.ppm";
    ImagenPPM imagenTest(imagenPrueba);

    ImagenPPM imagenClamp = tonemapping::clamp(imagenTest);
    ImagenPPM imagenEqualize = tonemapping::equalize(imagenTest);
    ImagenPPM imagenEqualizeClamp200 = tonemapping::equalizeClamp(imagenTest, 200);
    ImagenPPM imagenEqualizeClamp50 = tonemapping::equalizeClamp(imagenTest, 50);
    ImagenPPM imagenGamma = tonemapping::gamma(imagenTest, 2.2);
    ImagenPPM imagenGammaClamp = tonemapping::gammaClamp(imagenTest, 2.2);

    vector<ImagenPPM> imagenes = {imagenClamp, imagenEqualize, imagenEqualizeClamp200, imagenEqualizeClamp50, imagenGamma, imagenGammaClamp};
    for(int i = 0; i < imagenes.size(); i++) {
        string nombre = "ImagenPrueba_" + to_string(i) + ".ppm";
        imagenes[i].escrituraPPM(nombre);
    }
    cout << "Finalizacion del test: test_ImagenTonemappingColor ----------------" << endl;
}



int main(){

    cout << "Elige el test a ejecutar:" << endl;
    cout << "\t 1 - test_ImagenTonemappingColor" << endl;

    int eleccion;
    cin >> eleccion;

    switch (eleccion){
    case 1:
        test_ImagenTonemappingColor();
        break;
    
    default:
        break;
    }

}