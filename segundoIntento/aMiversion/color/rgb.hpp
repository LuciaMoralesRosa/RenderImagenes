#pragma once

#define R 0
#define G 1
#define B 2

#include <iostream>
#include <algorithm>
#include <cmath>

#include "../aleatorios/generadorAleatorios.hpp"

using namespace std;

/**
 * @class RGB
 * @brief Representa un color en el espacio RGB (Rojo, Verde, Azul).
 *
 * La clase `RGB` modela un color utilizando los componentes de color rojo,
 * verde y azul (R, G, B). 
 * Proporciona operaciones para manipular colores y acceder a los valores
 * individuales de los componentes RGB, así como realizar operaciones
 * aritméticas entre colores.
 */
class RGB {

private:
	/** 
     * @brief Valores de los componentes RGB del color.
     *
     * - `r`: El valor del componente rojo del color.
     * - `g`: El valor del componente verde del color.
     * - `b`: El valor del componente azul del color.
     */
    double r, g, b;
    double c[3] = {r, g, b};

public:
    
    /** 
     * @brief Constructor sin parámetros.
     * 
     * Inicializa el color en negro, con todos los componentes (R, G, B) en 0.
     */
	RGB();

	/** 
     * @brief Constructor con valores de componentes RGB.
     * 
     * @param red El valor del componente rojo del color.
     * @param green El valor del componente verde del color.
     * @param blue El valor del componente azul del color.
     */
	RGB(double red, double green, double blue);

	/** 
     * @brief Constructor con un solo valor (para colores en escala de grises).
     * 
     * @param w El valor para los componentes R, G y B.
     */
	RGB(double w);

    /** 
     * @brief Destructor.
     * 
     * El destructor no realiza ninguna acción específica, ya que no se utilizan recursos dinámicos.
     */
    ~RGB() {}


	/**
     * @brief Devuelve el valor máximo entre los componentes RGB.
     * 
     * @return El valor máximo entre `r`, `g` y `b`.
     */
	double maxC() const;

	/**
     * @brief Devuelve el valor máximo entre los componentes RGB y el canal
     * correspondiente.
     * 
     * @param canal Referencia para devolver el canal (R, G o B) que contiene el
     * valor máximo.
     * @return El valor máximo entre `r`, `g` y `b`.
     */
	double maxC(char& canal) const;

    /**
     * @brief Calcula la suma de los componentes RGB.
     * 
     * @return La suma de los valores de los componentes `r`, `g`, y `b`.
     */
	double sumarComponentes();

    /**
     * @brief Verifica si el color es nulo.
     * 
     * @return true si los valores de R, G y B son todos iguales a -1.
     */
    bool esNulo() const;

    /**
     * @brief Verifica si el color es negro.
     * 
     * @return true si los valores de R, G y B son todos iguales a 0.
     */
    bool esNegro() const;

    /**
     * @brief Verifica si el color es blanco.
     * 
     * @return true si los valores de R, G y B son todos iguales a 1.
     */
    bool esBlanco() const;

    // OPERADORES

	/**
     * @brief Suma de dos colores.
     * 
     * @param c1 El primer color.
     * @param c2 El segundo color.
     * @return Un nuevo color que es la suma de `c1` y `c2`.
     */
	friend RGB operator+(const RGB& c1, const RGB& c2);

	/**
     * @brief Suma un color a otro (operador `+=`).
     * 
     * @param c1 El primer color.
     * @param c2 El segundo color.
     * @return El color resultante de sumar `c2` a `c1`.
     */
	friend RGB operator+=(RGB& c1, const RGB& c2);

	/**
     * @brief Resta de dos colores.
     * 
     * @param c1 El primer color.
     * @param c2 El segundo color.
     * @return Un nuevo color que es la resta de `c2` de `c1`.
     */
	friend RGB operator-(const RGB& c1, const RGB& c2);

	/**
     * @brief Resta un color de otro (operador `-=`).
     * 
     * @param c1 El primer color.
     * @param c2 El segundo color.
     * @return El color resultante de restar `c2` a `c1`.
     */
	friend RGB operator-=(RGB& c1, const RGB& c2);

	/**
     * @brief Multiplicación de un color por un escalar.
     * 
     * @param c El color.
     * @param k El escalar.
     * @return Un nuevo color que es el resultado de multiplicar `c` por `k`.
     */
	friend RGB operator*(const RGB& c, double k);

	/**
     * @brief Multiplicación de un color por un escalar (operador `*=`).
     * 
     * @param c El color.
     * @param k El escalar.
     * @return El color resultante de multiplicar `c` por `k`.
     */
	friend RGB operator*=(RGB& c, double k);

	/**
     * @brief Multiplicación de un escalar por un color.
     * 
     * @param k El escalar.
     * @param c El color.
     * @return Un nuevo color que es el resultado de multiplicar `k` por `c`.
     */
	friend RGB operator*(double k, const RGB& c);

	/**
     * @brief Multiplicación componente a componente de dos colores.
     * 
     * @param c1 El primer color.
     * @param c2 El segundo color.
     * @return Un nuevo color que es el resultado de multiplicar componente a componente `c1` y `c2`.
     */
	friend RGB operator*(const RGB& c1, const RGB& c2);
	
    /**
     * @brief Multiplicación componente a componente de dos colores (operador `*=`).
     * 
     * @param c1 El primer color.
     * @param c2 El segundo color.
     * @return El color resultante de multiplicar componente a componente `c1` y `c2`.
     */
	friend RGB operator*=(RGB& c1, const RGB& c2);
	
	/**
     * @brief División de un color por un escalar.
     * 
     * @param c El color.
     * @param k El escalar.
     * @return Un nuevo color que es el resultado de dividir `c` entre `k`.
     */
	friend RGB operator/(const RGB& c, double k);
	
    /**
     * @brief División de un color por un escalar (operador `/=`).
     * 
     * @param c El color.
     * @param k El escalar.
     * @return El color resultante de dividir `c` entre `k`.
     */
	friend RGB operator/=(RGB& c, double k);

	/**
     * @brief Compara si dos colores son iguales.
     * 
     * @param c1 El primer color.
     * @param c2 El segundo color.
     * @return `true` si `c1` es igual a `c2`, `false` en caso contrario.
     */
	friend bool operator==(RGB c1, RGB c2);
	
    /**
     * @brief Compara si dos colores son diferentes.
     * 
     * @param c1 El primer color.
     * @param c2 El segundo color.
     * @return `true` si `c1` es diferente de `c2`, `false` en caso contrario.
     */
	friend bool operator!=(RGB c1, RGB c2);

    /**
     * @brief Acceso a los valores de los componentes RGB.
     * 
     * @param i El índice del componente (0 para R, 1 para G, 2 para B).
     * @return El valor del componente RGB correspondiente.
     */
	const double& operator[](int i) const;


    /**
     * @brief Escribe el color en el flujo de salida.
     * 
     * @param o El flujo de salida.
     * @param c El color a escribir.
     * @return El flujo de salida.
     */
	friend ostream &operator<< (ostream &o, const RGB &c);

    /**
     * @brief Lee el color desde el flujo de entrada.
     * 
     * @param i El flujo de entrada.
     * @param c El color a leer.
     * @return El flujo de entrada.
     */
	friend istream &operator>> (istream &i, RGB &c);
	
};