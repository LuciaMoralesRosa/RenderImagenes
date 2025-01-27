#pragma once

#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <sstream>
#include <ctime>

#include "../aleatorios/random.hpp"
#include "../aleatorios/randomBRDF.hpp"
#include "../color/rgb.hpp"
#include "../escena/camara.hpp"
#include "../escena/luz.hpp"
#include "../primitivas/primitiva.hpp"
#include "divisorSecciones.hpp"
#include "../materiales/brdf.hpp"


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


/**
 * @brief Calcula el color de la interseccion
 * 
 * @param primitiva La primitiva con la que se ha intersectado
 * @param primitivas Lista de primitivas
 * @param pIntersecciion Punto de interseccion
 * @param luz Luz
 * @param camara Camara
 * @param colorDisipado Color disipado
 * @param efecto Efecto
 * @param direccionRayo Direccion del rayo
 */
RGB colorInterseccion(const Primitiva* primitiva, list<Primitiva*> primitivas,
	const Punto& pInterseccion, Luz& luz, const Camara& camara,
	RGB& colorDisipado, Efecto efecto, Direccion direccionRayo);


/**
 * @brief Captura una seccion de la imagen
 */
void renderizarSeccion(Camara& camara, list<Primitiva*> primitivas,
	vector<Luz> luces, int rpp, int minX, int maxX,	int minY, int maxY,
	vector<RGB>& valoresPixeles);

/**
 * @brief Path tracing
 */
void pathTracing(Camara& camara, list<Primitiva*> primitivas,
	vector<Luz> luces, int rpp, int hilos, string fileName);