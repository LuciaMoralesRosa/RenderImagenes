#pragma once

#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <cstdint>

#include "../aleatorios/generadorAleatorios.hpp"
#include "../aleatorios/randomBRDF.hpp"
#include "material.hpp"
#include "../geometria/direccion.hpp"
#include "../geometria/punto.hpp"

enum Efecto {DIFUSO, REFLEXION, REFRACCION, LUZ, ABSORCION};


class BRDF {
	private:


public:
    RGB kd, ks, kt, kl;
    float nRefraction;
    char majorCh;
    Direccion normal;
	BRDF(const Material& material, Direccion normal) : kd(material.kd),
		ks(material.ks), kt(material.kt), kl(material.kl),
		nRefraction(material.nRefraction), majorCh(material.majorCh),
		normal(normal) {}


    // Gets the phenomenom that the ray suffers when it intersects the figure.
	Efecto obtenerEfecto () const {
		float r = russianRoulette.get();
		float aux = kd[majorCh];
		if (r < aux) return DIFUSO;
		aux += ks[majorCh];
		if (r < aux) return REFLEXION;
		aux += kt[majorCh];
		if (r < aux) return REFRACCION;
		aux += kl[majorCh];
		if (r < aux) return LUZ;
		return ABSORCION;
	}

	// Gets the color of the figure at the intersection point p.
	RGB getFrDiffuse() {
		return kd / (M_PI * kd[majorCh]);
	}

	// Gets the color of the figure at the intersection point p.
	RGB getFr(Efecto ph, Direccion& d, Punto p) const {
		Direccion wi;
		Direccion normal, aux;
		float eta;
		switch (ph) {
			case DIFUSO:
				aux = randBounce(p);
				d = escalar(aux, d) < 0 ? aux : -aux;
				return kd / (M_PI * kd[majorCh]);
			case REFLEXION:
				d = reflectionBounce(d, p);
				return ks / ks[majorCh];
			case REFRACCION:
				wi = d;
				wi = -wi.normalizar();
				if(escalar(wi, normal) < 0){
					normal = -normal;
					eta = nRefraction / 1;
				} else{
					eta = 1 / nRefraction;
				}
				d = refractionBounce(wi, normal, eta);
				return kt / kt[majorCh];
			case LUZ:
				return kl / kl[majorCh];
			default:
				return RGB();
		}
	}

	// Gets a random direction to bounce the ray.
	Direccion randBounce(const Punto& p) const {
		Direccion res = Direccion(normalGenerator.get(), normalGenerator.get(), normalGenerator.get());
		if (res.modulo() > 1)
				res = Direccion(normalGenerator.get(), normalGenerator.get(), normalGenerator.get());
		return escalar(res, normal) > 0 ? res.normalizar() : -res.normalizar();
	}

	// Gets the direction of a reflection bounce.
	Direccion reflectionBounce (const Direccion& d, const Punto& p) const {
			Direccion dNorm = d.normalizar();
			Direccion localNormal = normal;
			if (escalar(dNorm, localNormal) < 0) {
				localNormal = -localNormal;
			}
			return (dNorm - 2 * localNormal * escalar(dNorm, localNormal)).normalizar();
		}

	// Gets the direction of a refraction bounce, using eta as the ratio of
	// refraction indexes.
	Direccion refractionBounce (const Direccion& wi, const Direccion& n, float eta) const {
		float cosThetaI = escalar(n, wi);
		float sin2ThetaI = max(0.f, 1.0f - cosThetaI * cosThetaI);
		float sin2ThetaT = eta * eta * sin2ThetaI;
		float cosThetaT = sqrt(1 - sin2ThetaT);
		return eta * -wi + (eta * cosThetaI - cosThetaT) * n;
	}
};