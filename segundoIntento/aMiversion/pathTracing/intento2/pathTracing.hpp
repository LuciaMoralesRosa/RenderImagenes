#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <sstream>
#include <ctime>

#include "spaceSectioner.h"
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
#include "../varios/misc.hpp"
#include "../escena/camara.hpp"

RGB getColorOfHit (const Primitiva* figure, list<Primitiva*> figures, const Punto& hit,
					 Luz& lightSource, const Camara& camera, RGB& scatter,
					 Efecto ph, Direccion direccionCamara);


void captureSection(Camara& camera, list<Primitiva*> figures, vector<Luz> luces,
					int rpp, int minX, int maxX, int minY, int maxY,
					vector<RGB>& pixelsValue);

void captureSlave (Camara& camera, list<Primitiva*> figures, vector<Luz> luces,
				int rpp, SpaceSectioner& tiles, vector<RGB>& pixelsValue);

void pathTracing(Camara& camera, list<Primitiva*> figures, vector<Luz> luces,
				int rpp, int threads, string fileName);