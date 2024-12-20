#include "camara.hpp"

list<Rayo> Camara::rayoPorPixel(unsigned int x, unsigned int y, unsigned int nRayos) const {
    list<Rayo> listaDeRayos;

    Coordenada baseCamara(l, u, f, origen, 1);

    default_random_engine generador;
    uniform_real_distribution<double> rnd(0, 1);
    uniform_real_distribution<double> rndDepth(0, 0.02);

    for(int i = 0; i < nRayos; i++) {
        Direccion rayFocus(0,0,1);
        Direccion depthDisplace(rndDepth(generador), rndDepth(generador), 0);

        double nuevaX = ((double)x + rnd(generador)) / (double)tamPlanoImagen[0] * -2 + 1;
        double nuevaY = ((double)y + rnd(generador)) / (double)tamPlanoImagen[1] * -2 + 1;
        rayFocus.setX(nuevaX);
        rayFocus.setY(nuevaY);

        Coordenada direccionRayo(Vector3(1,0,0), Vector3(0,1,0), Vector3(0,0,1), (rayFocus - depthDisplace).getVector(), 0);
        Coordenada origenRayo(Vector3(1,0,0), Vector3(0,1,0), Vector3(0,0,1), depthDisplace.getVector(), 1);

        Coordenada nuevaDireccionRayo = baseCamara(direccionRayo);
        Coordenada nuevoOrigenRayo = baseCamara(origenRayo);

        Rayo r(Punto(nuevoOrigenRayo.getPosition()), Direccion(nuevaDireccionRayo.getPosition()));

        listaDeRayos.push_back(r);
    }
    return listaDeRayos;
}

