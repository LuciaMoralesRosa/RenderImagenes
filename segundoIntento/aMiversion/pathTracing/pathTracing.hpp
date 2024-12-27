
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <sstream>
#include <ctime>

#include "gestorDeSecciones.h"
#include "../color/rgb.hpp"
#include "../escena/luz.hpp"
#include "../geometria/punto.hpp"
#include "../geometria/rayo.hpp"
#include "../geometria/direccion.hpp"
#include "../materiales/material.hpp"
#include "../materiales/brdf.hpp"
#include "../primitivas/primitiva.hpp"
#include "../primitivas/esfera.hpp"
#include "../primitivas/plano.hpp"
#include "../aleatorios/generadorAleatorios.hpp"
#include "../escena/camara.hpp"
#include "../imagen/imagenPPM.hpp"  

RGB colorInterseccion (const Primitiva* primitiva, list<Primitiva*> primitivas, const Punto& pInter,
    Luz& luz, const Camara& camara, RGB& colorDisipado, Efecto efecto,
    Direccion direccionCamara);

void captureSection(Camara& camara, list<Primitiva*> primitivas, vector<Luz> luces,
int rpp, int minX, int maxX, int minY, int maxY, vector<RGB>& valoresPixeles);

void captureSlave (Camara& camara, list<Primitiva*> primitivas, vector<Luz> luces,
    int rpp, GestorDeSecciones& tiles, vector<RGB>& valoresPixeles);

void pathTracing(Camara& camara, list<Primitiva*> primitivas, vector<Luz> luces,
    int rpp, int threads, string fileName);