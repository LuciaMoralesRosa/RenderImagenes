#pragma once

#include "../misc/utilities.hpp"

#include <mutex>
#include <iostream>
#include <cmath>

using namespace std;

class DivisorSecciones {
    private:
    mutex mutex;
    int base, altura, nSeccionesX, nSeccionesY;
    int seccionX, seccionY;
    int iteracion, nSecciones;

    bool divisionCompleta;


    public:
    /**
     * @brief Constructor de la clase DivisorSecciones
     * 
     * @param b Base de la imagen
     * @param a Altura de la imagen
     * @param hilos Número de secciones en las que se dividirá la imagen
     */
    DivisorSecciones(int b, int a, int hilos) : base(b), altura(a),
        nSecciones(hilos), seccionX(0), seccionY(0), divisionCompleta(false), 
        iteracion(0) {
        pair<int, int> factores = encontrarFactores(hilos);
        cout << "Numero de secciones: "<< factores.first << ", " << factores.second << endl;
        nSeccionesX = factores.first;
        nSeccionesY = factores.second;

        cout << "Renderizado: 0%" << endl;
    }

        
    pair<int, int> encontrarFactores(int N) {
        if (N <= 0) return {-1, -1};  // Manejo de error para números no positivos
        
        int raiz = sqrt(N);
        
        // Si N es par, probamos con 2 primero
        if (N % 2 == 0) return {N / 2, 2};

        // Buscar el factor más cercano a la raíz cuadrada
        for (int i = raiz; i > 0; --i) {
            if (N % i == 0) {
                return {i, N / i};  // Primer par encontrado
            }
        }
        
        return {1, N};  // Si no hay factores mejores (solo ocurre si N es primo)
    }


    bool obtenerSeccion(RangoSeccion& puntosSeccion) {
		mutex.lock();
		if (divisionCompleta) {
            // Ya no quedan mas secciones por tratar
            cout << "No quedan mas secciones" << endl;
			mutex.unlock();
            // Cada hilo recibira su false
			return false;
		}

        // Definicion de las esquinas de la seccion
        EsquinaPixeles esqSupIzq = {seccionX * base / nSeccionesX,
                                    seccionY * altura / nSeccionesY};
        
        EsquinaPixeles esqInfDcha = {seccionX * base / nSeccionesX + base / nSeccionesX,
                                     seccionY * altura / nSeccionesY + altura / nSeccionesY};

        puntosSeccion = {esqSupIzq, esqInfDcha};

        cout << "calculos de las esquinas:  \n\tEsqSupIzq: " << esqSupIzq.ejeX << "-" << esqSupIzq.ejeY << "\n\tEsqInfDcha: "  << esqInfDcha.ejeX << "-" << esqInfDcha.ejeY << endl;

        // Actualizacion y comprobacion de valores limites
        if(++seccionX == nSeccionesX) {
            seccionX = 0;

            if(++seccionY == nSeccionesY) {
                divisionCompleta = true;
            }
        }

        // Por pantalla
    	//cout << "\033[" << 1 << "A";
		cout << "Renderizado: " << (++iteracion * 100 / nSecciones) << "%" << endl;

		mutex.unlock();
		return true;
	}

};