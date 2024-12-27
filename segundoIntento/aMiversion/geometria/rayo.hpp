#pragma once

#include "vector.hpp"
#include "direccion.hpp"
#include "punto.hpp"

/**
 * @class Rayo
 * @brief Representa un rayo en el espacio tridimensional, definido por un punto
 * de origen y una dirección.
 */
class Rayo {

    // Punto de origen y dirección del rayo.
	Vector origen, direccion;

public:

	/**
     * @brief Constructor por defecto.
     *
     * Inicializa el rayo con el punto de origen y la dirección predeterminados.
     */
    Rayo();

    /**
     * @brief Constructor con parámetros.
     * @param p El punto de origen del rayo.
     * @param d La dirección del rayo.
     *
     * Inicializa el rayo con un punto de origen p y una dirección d.
     */
	Rayo(const Punto& p, const Direccion& d);


    // GETTERS

	/**
     * @brief Obtiene el punto de origen del rayo.
     * @return El punto de origen p del rayo.
     */
    Vector obtenerOrigen() const { return origen; }

    /**
     * @brief Obtiene la dirección del rayo.
     * @return La dirección d del rayo.
     */
	Vector obtenerDireccion() const { return direccion; }

    /**
     * @brief Calcula un punto en el rayo a una distancia t desde el punto de
     * origen.
     * 
     * @param t El parámetro escalar que determina la distancia a lo largo del
     * rayo.
     * @return El punto calculado en el rayo, que está a una distancia t desde
     * el punto de origen.
     */
	Vector operator()(float t) const;

};
