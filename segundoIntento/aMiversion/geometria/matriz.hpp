#pragma once

#define _USE_MATH_DEFINES
#define DIM 4

#include <iostream>
#include <ostream>
#include <iomanip>
#include <cmath>
#include <math.h>

#include "vector.hpp"

using namespace std;

/**
 * @class Matriz
 * @brief Representa una matriz 4x4 para operaciones de transformación y
 * manipulación.
 *
 * La clase Matriz permite realizar diversas operaciones matemáticas comunes,
 * incluyendo translaciones, escalas, rotaciones en los ejes X, Y y Z,
 * así como la inversión de la matriz y otras funcionalidades auxiliares.
 */
class Matriz {

private:
	// Matriz representada como un arreglo 4x4.
	double m[DIM][DIM];

    /**
     * @brief Intercambia dos filas de la matriz.
     * @param matriz Matriz sobre la cual realizar la operación.
     * @param fila1 Índice de la primera fila.
     * @param fila2 Índice de la segunda fila.
     */
	void cambiarFilas(Matriz matriz, int fila1, int fila2);

public:

	/**
     * @brief Constructor por defecto.
     *
     * Inicializa todos los elementos de la matriz a 0.
     */
	Matriz();

    /**
     * @brief Constructor con matriz inicial.
     * @param m Arreglo 4x4 que representa los valores iniciales de la matriz.
     */
    Matriz(double m[DIM][DIM]);

	/**
     * @brief Convierte la matriz en una matriz de traslación.
     * @param x Desplazamiento en el eje X.
     * @param y Desplazamiento en el eje Y.
     * @param z Desplazamiento en el eje Z.
     */
	void matrizTraslacion(double x, double y, double z);

	/**
     * @brief Convierte la matriz en una matriz de escala.
     * @param x Escala en el eje X.
     * @param y Escala en el eje Y.
     * @param z Escala en el eje Z.
     */
	void matrizEscala(double x, double y, double z);

	/**
     * @brief Convierte la matriz en una matriz de rotación alrededor del eje X.
     * @param angulo Ángulo de rotación en grados.
     */
	void matrizRotacionX(double angulo);

	/**
     * @brief Convierte la matriz en una matriz de rotación alrededor del eje Y.
     * @param angulo Ángulo de rotación en grados.
     */
	void matrizRotacionY(double angulo);

	/**
     * @brief Convierte la matriz en una matriz de rotación alrededor del eje Z.
     * @param angulo Ángulo de rotación en grados.
     */
	void matrizRotacionZ(double angulo);
	
	 /**
     * @brief Invierte la matriz actual utilizando el método de Gauss-Jordan.
     * @return `true` si la matriz fue invertida con éxito, `false` si no es invertible.
     */
	bool invertirMatriz();

	/**
     * @brief Convierte la matriz en una matriz identidad.
     */
	void matrizIdentidad();

	/**
     * @brief Establece el valor de la matriz en una posición específica.
     * @param i Índice de la fila.
     * @param j Índice de la columna.
     * @param valor Valor a establecer.
     */
	void establecerComponente(int i, int j, double valor);

	/**
     * @brief Obtiene el valor de la matriz en una posición específica.
     * @param i Índice de la fila.
     * @param j Índice de la columna.
     * @return Valor almacenado en la posición (i, j).
     */
	double obtenerComponente(int i, int j) const;

	/**
     * @brief Sobrecarga del operador `<<` para imprimir la matriz.
     * @param o Flujo de salida.
     * @param m Matriz a imprimir.
     * @return Flujo de salida con la matriz formateada.
     */
	friend ostream &operator<<(ostream &o, const Matriz &m);
};
