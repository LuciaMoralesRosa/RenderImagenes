#pragma once

#include "primitiva.hpp"


/**
 * @class Plano
 * @brief Representa un plano en un espacio tridimensional.
 *
 * La clase define un plano mediante su normal y su distancia al origen de
 * coordenadas. También incluye métodos para calcular intersecciones con rayos
 * y verificar su relación con la luz y la cámara.
 */
class Plano : public Primitiva {
	
	Direccion n;   // Normal del plano.
    float d;       // Distancia desde el plano al origen de coordenadas.

public:

    /**
     * @brief Constructor que inicializa el plano con una normal, una distancia
     * al origen y un material.
     * 
     * @param id Identificador único del plano.
     * @param normal Dirección que define la orientación del plano.
     * @param distancia Distancia del plano al origen de coordenadas.
     * @param material Material asociado al plano.
     */	Plano (const uint16_t id, const Direccion& normal, float distancia, 
           const Material& material) : n(normal.normalizar()), d(distancia),
           Primitiva(id, material) {}

	/**
     * @brief Constructor que inicializa el plano con una normal, un punto en
     * el plano y un material.
     * 
     * La distancia al origen se calcula en función de la normal y el punto
     * proporcionados.
     * 
     * @param id Identificador único del plano.
     * @param normal Dirección que define la orientación del plano.
     * @param p Punto que pertenece al plano.
     * @param material Material asociado al plano.
     */
	Plano (const uint16_t id, const Direccion& normal, const Punto& p,
           const Material& material) :
		   n(normal.normalizar()),
           d(abs(escalar(n, distancia(Punto(0,0,0), p)))),
           Primitiva(id, material) {}
			

	/**
     * @brief Comprueba si un rayo intersecta el plano y, si es así, calcula la
     * distancia a la intersección.
     * 
     * @param r Rayo a evaluar.
     * @param t Referencia para almacenar la distancia desde el origen del rayo
     *          hasta el punto de intersección.
     * @return true Si el rayo intersecta el plano, false si no.
     */
	bool intersecta(const Rayo& r, float& t) const override {
		float denom = escalar(r.obtenerDireccion(), n);
		if (abs(denom) > 1e-6) {
			t = -(d - escalar(distancia(Punto(0,0,0), r.obtenerOrigen()), n))
                / denom;
			return t >= 0;
		}
		// If not, then it's false (because tray and plane are parallel).
		return false;
	}

    /**
     * @brief Comprueba si el plano está entre la cámara y una fuente de luz.
     * 
     * Evalúa si el plano bloquea la luz proveniente de una fuente, verificando
     * si hay intersección entre el rayo desde la cámara hacia la luz y el plano.
     * 
     * @param camera Cámara desde la que se evalúa.
     * @param luz Fuente de luz a considerar.
     * @param p Punto en el plano (no utilizado directamente en el cálculo).
     * @return true Si el plano bloquea la luz, false si no.
     */
    bool planoContraLuz(const Camara& camera, const Luz& luz, const Punto& p)
        const override {
		float t;
		Direccion direccionRayo = distancia(luz.centro, camera.o);
		return this->intersecta(Rayo(camera.o, direccionRayo), t) && t < 1;
	}

    // GETTERS

    /**
     * @brief Obtiene la normal del plano en un punto dado.
     * 
     * @param p Punto de referencia (no influye en el cálculo de la normal).
     * @return Direccion La normal del plano.
     */
	Direccion obtenerNormal(const Punto& p) const override { return n; }

};