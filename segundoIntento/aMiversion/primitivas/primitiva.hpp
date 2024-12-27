#pragma once

#include <cmath>
#include <cstdint>

#include "../color/rgb.hpp"
#include "../escena/luz.hpp"
#include "../escena/camara.hpp"	
#include "../geometria/rayo.hpp"
#include "../geometria/punto.hpp"
#include "../geometria/direccion.hpp"
#include "../materiales/material.hpp"

// Class that represents any figure.
class Primitiva {

public:

	Material material;

public:
	// Constructor.
	Primitiva (const uint16_t id, const Material& material) : material(material) {}

	// Destructor.
	virtual ~Primitiva() {}

	Material obtenerMaterial() const {
		return material;
	}

	// Checks if the ray intersects the figure and returns the distance to the
	// intersection point.
	virtual bool intersecta(const Rayo& rayo, float& t) const = 0;

	// Checks if the plane is between the camera and the light source so that
	// means that the light source is not visible from the camera at that point.
	virtual bool planoContraLuz(const Camara& camara,
							const Luz& luz, const Punto& p) const = 0;

	// Gets the normal of the figure at the intersection point p.
	virtual Direccion obtenerNormal(const Punto& p) const = 0;

	

};