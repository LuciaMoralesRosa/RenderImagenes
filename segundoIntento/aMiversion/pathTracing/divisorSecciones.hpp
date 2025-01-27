#pragma once

#include <mutex>
#include <iostream>

using namespace std;

class DivisorSecciones {
    private:
    mutex mutex;
    int base, altura, nSecciones;
    int ejeX, ejeY;
    int iteracion, totalSecciones;

    bool final;


    public:
    /**
     * @brief Constructor de la clase DivisorSecciones
     * 
     * @param b Base de la imagen
     * @param a Altura de la imagen
     * @param s Número de secciones en las que se dividirá la imagen
     */
    DivisorSecciones(int b, int a, int s) : base(b), altura(a), nSecciones(s),
        final(false), iteracion(0), totalSecciones(s*s), ejeX(0), ejeY(0) {
        cout << "Renderizado: 0%" << endl;
    }

    bool obtenerSeccion(int& minX, int& maxX, int& minY, int& maxY) {
		mutex.lock();
		if (final) {
            // Ya no quedan mas secciones por tratar
			mutex.unlock();
            // Cada hilo recibira su false
			return false;
		}

        // Establecer valores de los ejes de la seccion
		minX = ejeX * base / nSecciones;
		maxX = (ejeX + 1) * base / nSecciones;
		minY = ejeY * altura / nSecciones;
		maxY = (ejeY + 1) * altura / nSecciones;

        // Por pantalla
    	cout << "\033[" << 1 << "A";
		cout << "Renderizado: " << (++iteracion*100/totalSecciones) << "%" << endl;
		if (++ejeY == nSecciones) {
			ejeY = 0;
			if (++ejeX == nSecciones){
                final = true;
            }
		}

		mutex.unlock();
		return true;
	}

};