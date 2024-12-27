#ifndef SPACESECTIONER_H
#define SPACESECTIONER_H
#pragma once

#include <mutex>
#include <iostream>
using namespace std;

// Object that divides a given space into sections.
class GestorDeSecciones {
private:
	int base, altura; // Dimensiones del espacio
	int seccionesX, seccionesY; // Numero de secciones para cada eje
	int i, j, iter, total; // Indices de seccion y variables de control

	bool done = false; // Flag de terminacion

	mutex mMutex; // Mutex para controlar la concurrencia

public:

	// Constructor.
	GestorDeSecciones(int base, int altura, int hilos) :
		base(base), altura(altura), seccionesX(hilos), seccionesY(hilos),
		i(0), j(0), iter(0), total(hilos * hilos), done (false) {
		cout << "Space managed: 0%" << endl;
	}


	bool getSection(int& minX, int& maxX, int& minY, int& maxY) {
		mMutex.lock();

		// Comprobar si quedan secciones por evaluar
		if (done) {
			// Si no quedan secciones, devolver false
			mMutex.unlock();
			return false;
		}

		// Obtener valores para los intervalos a evaluar
		minX = i * base / seccionesX;
		maxX = (i + 1) * base / seccionesX;
		minY = j * altura / seccionesY;
		maxY = (j + 1) * altura / seccionesY;

		// Actualizar el porcentaje de secciones evaluadas
    	cout << "\033[" << 1 << "A";
		cout << "Space managed: " << (++iter*100/total) << "%" << endl;

		// Actualizar los indices de seccion
		if (++j == seccionesY) {
			j = 0;
			if (++i == seccionesX) {
				done = true;
			} 
		}
		mMutex.unlock();
		return true;
	}

};

#endif // SPACESECTIONER_H