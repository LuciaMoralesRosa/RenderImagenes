#pragma once

#include "vector.hpp"
#include "../aleatorios/generadorAleatorios.hpp"
#include "../aleatorios/random.hpp"

/**
 * @class Direccion
 * @brief Representa una dirección en el espacio tridimensional.
 *
 * Esta clase extiende la clase Vector, pero en lugar de representar un punto
 * en el espacio, representa una dirección, lo que implica que la coordenada
 * isPoint se establece en 0.
 */
class Direccion : public Vector {
    
public:
/**
     * @brief Constructor por defecto.
     *
     * Inicializa la dirección en el vector nulo (0, 0, 0) y establece
     * isPoint en 0.
     */
    Direccion();

    /**
     * @brief Constructor con parámetros.
     * @param x Coordenada X de la dirección.
     * @param y Coordenada Y de la dirección.
     * @param z Coordenada Z de la dirección.
     *
     * Inicializa la dirección con las coordenadas (x, y, z) y establece
     * isPoint en 0.
     */
    Direccion(float x, float y, float z);

    /**
     * @brief Constructor de conversión desde un objeto Vector.
     * @param v Objeto Vector a convertir en una dirección.
     *
     * Convierte un objeto Vector en una dirección, y establece isPoint a 0.
     */
    Direccion(Vector v);

    /**
     * @brief Convierte una dirección en un vector 4D.
     * @param d La dirección a convertir.
     * @return Un objeto Vector representando la dirección con isPoint igual a 0.
     */
    friend Vector obtenerVector(Direccion d);

    /**
     * @brief Genera una dirección aleatoria en 3D.
     * @return Una dirección aleatoria.
     *
     * Utiliza generadores de números aleatorios (randPhi2 y randTheta2) para
     * generar una dirección aleatoria.
     */
    Direccion direccionAleatoria();

    /**
     * @brief Sobrecarga del operador de entrada para leer una dirección desde
     * el flujo de entrada.
     * @param i Flujo de entrada (istream).
     * @param d La dirección a llenar con los valores leídos.
     * @return Flujo de entrada con los valores de la dirección.
     *
     * Lee las coordenadas X, Y, Z de la dirección desde el flujo de entrada.
     */
    friend istream &operator>>(istream &i, Direccion &d);
};