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
#include "spaceSectioner.hpp"
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
void capturarSeccion(Camara& camara, list<Primitiva*> primitivas,
	vector<Luz> luces, int rpp, int minX, int maxX,	int minY, int maxY,
	vector<RGB>& valoresPixeles);


/**
 * @brief Captura un trabajador
 */
void capturarTrabajador(Camara& camara, list<Primitiva*> primitivas,
	vector<Luz> luces, int rpp, SpaceSectioner& tiles,
	vector<RGB>& valoresPixeles);


/**
 * @brief Path tracing
 */
void pathTracing(Camara& camara, list<Primitiva*> primitivas,
	vector<Luz> luces, int rpp, int threads, string fileName);