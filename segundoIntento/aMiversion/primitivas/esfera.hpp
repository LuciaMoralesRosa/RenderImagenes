#pragma once

#include "primitiva.hpp"

/**
 * @class Esfera
 * @brief Representa una esfera en un espacio tridimensional.
 *
 * La clase define una esfera mediante su centro y radio. Incluye métodos para
 * calcular la normal en un punto y verificar si un rayo intersecta con la esfera.
 */
class Esfera : public Primitiva {

	Punto c;	// Centro.
	float r;	// Radio.

public:

	/**
     * @brief Constructor para inicializar una esfera.
     * 
     * @param id Identificador único de la esfera.
     * @param c Punto que representa el centro de la esfera.
     * @param r Radio de la esfera.
     * @param material Material asociado a la esfera.
     */
	Esfera(const uint16_t id, const Punto& c, float r, const Material& material)
		: c(c), r(r), Primitiva(id, material) {}

	/**
     * @brief Obtiene la normal de la esfera en un punto dado.
	 * 
     * @param p Punto en la superficie de la esfera.
     * @return Direccion La normal en el punto `p`.
     */
	Direccion obtenerNormal(const Punto& p) const override {
		return distancia(p, c).normalizar();
	}
	
	/**
     * @brief Comprueba si un rayo intersecta con la esfera y, si es así,
	 * calcula la distancia a la intersección.
	 * 
     * @param ray Rayo a evaluar.
     * @param t Referencia para almacenar la distancia desde el origen del rayo
	 * 			hasta el punto de intersección.
     * @return true Si el rayo intersecta la esfera, false si no.
     */
	bool intersecta(const Rayo& rayo, float& t) const override {
		Vector oc = distancia(rayo.obtenerOrigen(), c);
		float a = escalar(rayo.obtenerDireccion(), rayo.obtenerDireccion());
		float b = 2 * escalar(oc, rayo.obtenerDireccion());
		float c = escalar(oc, oc) - r * r;
		float discriminant = b * b - 4 * a * c;
		if (discriminant < 0) {
			return false;
		}
		else {
			float t1 = (-b - sqrt(discriminant)) / (2 * a);
			float t2 = (-b + sqrt(discriminant)) / (2 * a);
			if (t1 < 0 && t2 < 0)
				return false;
			if (t1 >= 0){
				t = t1;
				return true;
			}
			if (t2 >= 0){
				t = t2;
				return true;
			}
			return true;
		}
	}

	/**
     * @brief Comprueba si la esfera bloquea la luz entre una cámara y una
	 * fuente de luz.
     * 
     * @param camera Cámara desde la que se evalúa.
     * @param light Fuente de luz a considerar.
     * @param p Punto en el plano (no utilizado en esta implementación).
     * @return false Siempre retorna falso.
     */
	bool planoContraLuz(const Camara& camera, const Luz& luz,
        const Punto& p) const override {
		return false;
	}

};