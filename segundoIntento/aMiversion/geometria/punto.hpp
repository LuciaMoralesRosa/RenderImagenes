#pragma once

#include "vector.hpp"

/**
 * @class Punto
 * @brief Representa un punto en el espacio tridimensional.
 *
 * Esta clase extiende la clase Vector, ajustando su comportamiento para
 * representar puntos en el espacio 3D, con el valor isPoint siempre
 * establecido en 1.
 */
class Punto : public Vector {

public:

    /**
     * @brief Constructor por defecto.
     *
     * Inicializa el punto en el origen (0, 0, 0).
     */
    Punto();

    /**
     * @brief Constructor con parámetros.
     * @param x Coordenada X del punto.
     * @param y Coordenada Y del punto.
     * @param z Coordenada Z del punto.
     *
     * Inicializa un punto en las coordenadas (x, y, z).
     */
    Punto(float x, float y, float z);

    /**
     * @brief Constructor de conversión desde un objeto Vector.
     * @param v Objeto Vector a convertir en un punto.
     *
     * Convierte un objeto Vector en un punto, configurando isPoint a 1.
     */
    Punto(Vector v);

    /**
     * @brief Convierte un punto en un vector de 4 dimensiones (isPoint = 1).
     * @param p El punto a convertir.
     * @return Un vector con las mismas coordenadas que el punto, pero con
     * isPoint igual a 1.
     */
	friend Vector obtenerVector(Punto p);
	
    /**
     * @brief Sobrecarga del operador de entrada para leer un punto desde el
     * flujo de entrada.
     * @param i Flujo de entrada (istream).
     * @param p El punto a llenar con los valores leídos.
     * @return Flujo de entrada con los valores del punto.
     *
     * Lee las coordenadas X, Y, Z del punto desde el flujo de entrada.
     */
	friend istream &operator>>(istream &i, Punto &p);
};
