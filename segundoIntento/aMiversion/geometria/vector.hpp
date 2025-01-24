#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <cstdint>
#include <string>
#include <iostream>
#include <ostream>
#include <array>

#include "matriz.hpp"

using namespace std;

class Matriz;

/**
 * @class Vector
 * @brief Representa un vector tridimensional, que puede ser un punto o una
 * dirección en el espacio 3D.
 *
 * Esta clase proporciona operaciones comunes con vectores, como suma, resta,
 * multiplicación por escalar, producto punto, producto cruzado, normalización,
 * entre otras. Además, soporta transformaciones geométricas como traslación,
 * rotación y escala mediante matrices.
 */
class Vector {

protected:

	// Coordenadas del vector
	float x, y, z;

	// 1 si el vector es un punto, 0 si es una dirección
	uint8_t esPunto;

    /**
     * @brief Aplica una matriz de transformación al vector.
     * @param m Matriz de transformación.
     */
	void aplicarMatriz(Matriz m);

public:

	/**
     * @brief Constructor por defecto.
     *
     * Inicializa el vector en el origen (0, 0, 0) y lo marca como una dirección.
     */
	Vector();
	/**
     * @brief Constructor con parámetros.
     * @param x Coordenada X del vector.
     * @param y Coordenada Y del vector.
     * @param z Coordenada Z del vector.
     * @param esPunto Determina si el vector es un punto (1) o una dirección (0).
     */
	Vector(float x, float y, float z, uint8_t esPunto);

    /**
     * @brief Devuelve el módulo (longitud) del vector.
     * @return El módulo del vector.
     */
	float modulo() const;

    /**
     * @brief Normaliza el vector.
     * @return El vector normalizado.
     */
	Vector normalizar() const;

    /**
     * @brief Calcula el producto escalar entre dos vectores.
     * @param c1 Primer vector.
     * @param c2 Segundo vector.
     * @return Producto escalar de los vectores c1 y c2.
     */
	friend float escalar(const Vector &c1, const Vector &c2);

	/**
     * @brief Calcula el producto vectorial entre dos vectores.
     * @param c1 Primer vector.
     * @param c2 Segundo vector.
     * @return Vector resultado del producto vectorial.
     */
	friend Vector vectorial(const Vector &c1, const Vector &c2);

    /**
     * @brief Aplica una matriz de traslación al vector.
     * @param x Desplazamiento en X.
     * @param y Desplazamiento en Y.
     * @param z Desplazamiento en Z.
     */
	void trasladar(double x, double y, double z);

    /**
     * @brief Aplica una matriz de escala al vector.
     * @param x Factor de escala en X.
     * @param y Factor de escala en Y.
     * @param z Factor de escala en Z.
     */
	void escalar(double x, double y, double );

    /**
     * @brief Aplica una rotación al vector alrededor del eje X.
     * @param grados Ángulo de rotación en grados.
     */
	void rotarX(double grados);

    /**
     * @brief Aplica una rotación al vector alrededor del eje Y.
     * @param grados Ángulo de rotación en grados.
     */
	void rotarY(double grados);

    /**
     * @brief Aplica una rotación al vector alrededor del eje Z.
     * @param grados Ángulo de rotación en grados.
     */
	void rotarZ(double grados);

	/**
     * @brief Aplica un cambio de base al vector.
     * @param o Punto de origen para la nueva base.
     * @param u Vector base para el nuevo sistema de coordenadas (u, v, w).
     * @param v Vector base para el nuevo sistema de coordenadas (u, v, w).
     * @param w Vector base para el nuevo sistema de coordenadas (u, v, w).
     */
	void cambiarBase(Vector o, Vector u, Vector v, Vector w);

	/**
     * @brief Aplica un cambio de base al vector y la invierte.
     * @param o Punto de origen para la nueva base.
     * @param u Vector base para el nuevo sistema de coordenadas (u, v, w).
     * @param v Vector base para el nuevo sistema de coordenadas (u, v, w).
     * @param w Vector base para el nuevo sistema de coordenadas (u, v, w).
     */
	void cambiarBaseInvertida(Vector o, Vector u, Vector v, Vector w);


	/**
     * @brief Convierte el vector a un array de 3 floats.
     * @return Array de tres elementos con las coordenadas X, Y, Z.
     */
	array<float, 3> convertirArray() const;

	/**
     * @brief Calcula el ángulo entre dos vectores de dirección.
     * @param c1 Primer vector.
     * @param c2 Segundo vector.
     * @return Ángulo entre los vectores en radianes.
     */
	friend double anguloEntreDirecciones(const Vector &c1, const Vector &c2);

    /**
     * @brief Calcula el vector de distancia entre dos puntos.
     * @param p1 Primer punto.
     * @param p2 Segundo punto.
     * @return Vector que representa la distancia entre p1 y p2.
     */
	friend Vector distancia(Vector p1, Vector p2);
    // GETTERS Y SETTERS

    /**
     * @brief Obtiene la coordenada X del vector.
     * @return Coordenada X.
     */
	double getX() const { return x;	}

    /**
     * @brief Obtiene la coordenada Y del vector.
     * @return Coordenada Y.
     */
	double getY() const { return y;	}

    /**
     * @brief Obtiene la coordenada Z del vector.
     * @return Coordenada Z.
     */
	double getZ() const { return z;	}

    /**
     * @brief Obtiene si el vector es un punto.
     * @return 1 si el vector es un punto, 0 si es una dirección.
     */
	uint8_t getEsPunto() const { return esPunto; }

    /**
     * @brief Obtiene si el vector es una dirección.
     * @return 1 si el vector es una dirección, 0 si es un punto.
     */
	uint8_t getEsDireccion() const { return 1 - esPunto; }

    /**
     * @brief Establece la coordenada X del vector.
     * @param x Nueva coordenada X.
     */
	void setX(double x) { this->x = x; }

    /**
     * @brief Establece la coordenada Y del vector.
     * @param y Nueva coordenada Y.
     */
	void setY(double y) { this->y = y; }

    /**
     * @brief Establece la coordenada Z del vector.
     * @param z Nueva coordenada Z.
     */
	void setZ(double z) { this->z = z; }


	// OPERADORES

    /**
     * @brief Sobrecarga del operador de suma para vectores.
     * @param c1 Primer vector.
     * @param c2 Segundo vector.
     * @return Vector resultante de la suma.
     */
	friend Vector operator+(const Vector &c1, const Vector &c2);

    /**
     * @brief Sobrecarga del operador de resta para vectores.
     * @param c1 Primer vector.
     * @param c2 Segundo vector.
     * @return Vector resultante de la resta.
     */
	friend Vector operator-(const Vector &c1, const Vector &c2);

    /**
     * @brief Sobrecarga del operador de negación para un vector.
     * @param c Vector a negar.
     * @return Vector con las coordenadas opuestas.
     */
	friend Vector operator-(const Vector &c);

    /**
     * @brief Sobrecarga del operador de multiplicación por un escalar.
     * @param c Vector a multiplicar.
     * @param s Escalar.
     * @return Vector resultante de la multiplicación.
     */
	friend Vector operator*(const Vector &c, const double &s);

    /**
     * @brief Sobrecarga del operador de multiplicación por un escalar.
     * @param s Escalar.
     * @param c Vector a multiplicar.
     * @return Vector resultante de la multiplicación.
     */
	friend Vector operator*(const double &s, const Vector &c);

	/**
     * @brief Sobrecarga del operador de división por un escalar.
     * @param c Vector a dividir.
     * @param s Escalar.
     * @return Vector resultante de la división.
     */
	friend Vector operator/(const Vector &c, const double &s);

    /**
     * @brief Sobrecarga del operador de división por un escalar.
     * @param s Escalar.
     * @param c Vector a dividir.
     * @return Vector resultante de la división.
     */
	friend Vector operator/(const double &s, const Vector &c);
	
    /**
     * @brief Sobrecarga del operador de igualdad.
     * @param c1 Primer vector.
     * @param c2 Segundo vector.
     * @return `true` si ambos vectores son iguales.
     */
	friend bool operator==(const Vector &c1, const Vector &c2);

	/**
     * @brief Acceso a las coordenadas del vector mediante índice.
     * @param i Índice de la coordenada (0: X, 1: Y, 2: Z).
     * @return Coordenada solicitada.
     */
	const float& operator[](int i) const;

	/**
     * @brief Sobrecarga del operador de salida para imprimir el vector.
     * @param o Flujo de salida.
     * @param c Vector a imprimir.
     * @return Flujo de salida con el vector formateado.
     */
	friend ostream &operator<<(ostream &o, const Vector &c);
};